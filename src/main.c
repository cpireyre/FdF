/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:45:09 by copireyr          #+#    #+#             */
/*   Updated: 2024/08/07 11:19:37 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_render_context	initialize_ctx(const char *name, t_arena a);
static void				render_frame(t_render_context *ctx);
static void				key_hook(mlx_key_data_t keydata, t_render_context *ctx);

int	main(int argc, char **argv)
{
	t_arena					a;
	t_render_context		ctx;

	if (argc == 2)
	{
		a = arena_new();
		if (!a)
			return (1);
		ctx = initialize_ctx(argv[1], a);
		ctx.num_lines = parse(argv[1], &ctx.lines, a);
		if (ctx.num_lines && ctx.init_success)
		{
			mlx_loop_hook(ctx.mlx, (t_hook)render_frame, &ctx);
			mlx_key_hook(ctx.mlx, (mlx_keyfunc)key_hook, &ctx);
			mlx_loop(ctx.mlx);
			serialize(ctx.t);
		}
		if (ctx.mlx)
			mlx_terminate(ctx.mlx);
		arena_dispose(&a);
	}
	else
		ft_dprintf(2, "Usage: ./fdf map.fdf\n");
	return (0);
}

static t_render_context	initialize_ctx(const char *name, t_arena a)
{
	t_render_context	ctx;

	ctx.dvd_mode_on = 0;
	ctx.z_buffer = arena_alloc(a, WIN_HEIGHT * WIN_WIDTH * sizeof(int));
	if (!ctx.z_buffer)
		return (ctx);
	ctx.init_success = 0;
	ctx.bg_color = BG_COLOR;
	ctx.t = deserialize(WIN_WIDTH, WIN_HEIGHT);
	mlx_set_setting(MLX_FULLSCREEN, FULLSCREEN);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	ctx.mlx = NULL;
	ctx.img = NULL;
	ctx.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, name, true);
	if (!ctx.mlx)
		return (ctx);
	ctx.img = mlx_new_image(ctx.mlx,
			WIN_WIDTH, WIN_HEIGHT);
	if (!ctx.img)
		return (ctx);
	ctx.image_size_in_pixels = ctx.img->width * ctx.img->height;
	if (mlx_image_to_window(ctx.mlx, ctx.img, 0, 0) != -1)
		ctx.init_success = 1;
	return (ctx);
}

static void	render_frame(t_render_context *ctx)
{
	t_line	current_line;
	t_line	*line;
	t_v3d	center;

	ft_memset_32(ctx->img->pixels, ctx->bg_color, ctx->image_size_in_pixels);
	ft_memset_32(ctx->z_buffer, (uint32_t)INT_MIN, WIN_WIDTH * WIN_HEIGHT);
	move(ctx->mlx, &ctx->t);
	if (ctx->dvd_mode_on)
		dvd(&ctx->t, WIN_WIDTH, WIN_HEIGHT);
	center = v3dd(0);
	line = ctx->lines - 1;
	while (++line != ctx->lines + ctx->num_lines)
		center = v3d_add(center, v3d_add(line->world0, line->world1));
	center = v3d_div(center, v3dd(2 * ctx->num_lines));
	while (line-- != ctx->lines)
	{
		current_line = transform(&ctx->t, center, *line);
		if (clip(&current_line, (int)ctx->img->width, (int)ctx->img->height))
			rasterize(ctx->img, ctx->z_buffer, current_line);
	}
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(ctx->mlx);
}

static void	key_hook(mlx_key_data_t keydata, t_render_context *ctx)
{
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		ctx->dvd_mode_on ^= 1;
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		ft_bzero(&ctx->t, sizeof(ctx->t));
		ctx->t.scale = 100;
		ctx->t.offset.y = (int)(ctx->img->height / 2);
		ctx->t.offset.x = (int)(ctx->img->width / 2);
	}
}
