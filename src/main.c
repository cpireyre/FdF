/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:45:09 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/28 15:05:18 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
void	serialize(t_transform T);
t_transform	deserialize(int default_width, int default_height);

static t_render_context	initialize_ctx(const char *name, int width, int height);
static void				render_frame(t_render_context *ctx);
static void				move(mlx_t *m, t_transform *T);

int	main(int argc, char **argv)
{
	t_arena					a;
	t_render_context		ctx;

	if (argc == 2)
	{
		a = arena_new();
		if (!a)
			return (1);
		ctx = initialize_ctx(argv[1], WIN_WIDTH, WIN_HEIGHT);
		ctx.num_lines = parse(argv[1], &ctx.lines, a);
		if (ctx.num_lines && ctx.init_success)
		{
			mlx_loop_hook(ctx.mlx, (t_hook)render_frame, &ctx);
			mlx_loop(ctx.mlx);
			serialize(ctx.T);
		}
		if (ctx.mlx)
			mlx_terminate(ctx.mlx);
		arena_dispose(&a);
	}
	else
		ft_dprintf(2, "Usage: ./fdf map.fdf\n");
	return (0);
}

static t_render_context	initialize_ctx(const char *name, int width, int height)
{
	t_render_context	ctx;

	ctx.init_success = 0;
	ctx.bg_color = BG_COLOR;
	ctx.T = deserialize(width, height);
	mlx_set_setting(MLX_FULLSCREEN, false);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	ctx.mlx = NULL;
	ctx.img = NULL;
	ctx.mlx = mlx_init(width, height, name, true);
	if (!ctx.mlx)
		return (ctx);
	ctx.img = mlx_new_image(ctx.mlx,
			(uint32_t)width, (uint32_t)height);
	if (!ctx.img)
		return (ctx);
	ctx.image_size_in_pixels = ctx.img->width * ctx.img->height;
	if (mlx_image_to_window(ctx.mlx, ctx.img, 0, 0) != -1)
		ctx.init_success = 1;
	return (ctx);
}

void	dvd(t_transform *T, int width, int height);
static void	render_frame(t_render_context *ctx)
{
	int	i;
	t_line current_line;
	t_vecd	center;

	ft_memset_32(ctx->img->pixels, ctx->bg_color, ctx->image_size_in_pixels);
	move(ctx->mlx, &ctx->T);
	dvd(&ctx->T, (int)ctx->img->width, (int)ctx->img->height);
	i = 0;
	center = calculate_center(ctx->lines, ctx->num_lines);
	while (i < ctx->num_lines)
	{
		current_line = transform(ctx->lines[i], &ctx->T, center);
		if (clip(&current_line, (int)ctx->img->width, (int)ctx->img->height))
			rasterize(ctx->img, current_line);
		i++;
	}
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(ctx->mlx);
}

static void	move(mlx_t *m, t_transform *T)
{
	if (mlx_is_key_down(m, MLX_KEY_RIGHT_ALT))
	{
		T->rotation.y -= 1 * (mlx_is_key_down(m, MLX_KEY_W));
		T->rotation.y += 1 * (mlx_is_key_down(m, MLX_KEY_S));
		T->rotation.x -= 1 * (mlx_is_key_down(m, MLX_KEY_A));
		T->rotation.x += 1 * (mlx_is_key_down(m, MLX_KEY_D));
		T->rotation.z -= 1 * (mlx_is_key_down(m, MLX_KEY_Q));
		T->rotation.z += 1 * (mlx_is_key_down(m, MLX_KEY_E));
	}
	else if (mlx_is_key_down(m, MLX_KEY_RIGHT_SHIFT))
	{
		T->scale += 1 * (mlx_is_key_down(m, MLX_KEY_W));
		T->scale -= 1 * (mlx_is_key_down(m, MLX_KEY_S));
		if (T->scale < 3)
			T->scale = 3;
	}
	else
	{
		T->offset_y -= 5 * (mlx_is_key_down(m, MLX_KEY_W));
		T->offset_x -= 5 * (mlx_is_key_down(m, MLX_KEY_A));
		T->offset_y += 5 * (mlx_is_key_down(m, MLX_KEY_S));
		T->offset_x += 5 * (mlx_is_key_down(m, MLX_KEY_D));
	}
}
