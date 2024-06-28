/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:45:09 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/28 13:39:43 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_render_context	initialize_ctx(const char *name, int width, int height);
static void				render_frame(t_render_context *ctx);
static void				move(mlx_t *m, t_projection *param);

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
		}
		if (ctx.mlx)
			mlx_terminate(ctx.mlx);
		arena_dispose(&a);
	}
	else
		ft_printf("Usage: ./fdf map.fdf\n");
	return (0);
}

static t_render_context	initialize_ctx(const char *name, int width, int height)
{
	t_render_context	ctx;

	ctx.init_success = 0;
	ctx.bg_color = BG_COLOR;
	ctx.param.scale = 100;
	ctx.param.angle = 45;
	ctx.param.offset_x = width / 3;
	ctx.param.offset_y = height / 2;
	mlx_set_setting(MLX_FULLSCREEN, true);
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

static void	render_frame(t_render_context *ctx)
{
	int	i;
	t_line current_line;

	ft_memset_32(ctx->img->pixels, ctx->bg_color, ctx->image_size_in_pixels);
	move(ctx->mlx, &ctx->param);
	i = 0;
	while (i < ctx->num_lines)
	{
		current_line = project_line(ctx->lines[i], &ctx->param);
		if (clip(&current_line, (int)ctx->img->width, (int)ctx->img->height))
			rasterize(ctx->img, current_line);
		i++;
	}
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(ctx->mlx);
}

static void	move(mlx_t *m, t_projection *param)
{
	if (mlx_is_key_down(m, MLX_KEY_RIGHT_SHIFT))
	{
		param->scale -= 1 * (mlx_is_key_down(m, MLX_KEY_W));
		param->angle -= 0.1F * (mlx_is_key_down(m, MLX_KEY_A));
		param->scale += 1 * (mlx_is_key_down(m, MLX_KEY_S));
		param->angle += 0.1F * (mlx_is_key_down(m, MLX_KEY_D));
		if (param->scale < 0)
			param->scale = 0;
	}
	else
	{
		param->offset_y -= 5 * (mlx_is_key_down(m, MLX_KEY_W));
		param->offset_x -= 5 * (mlx_is_key_down(m, MLX_KEY_A));
		param->offset_y += 5 * (mlx_is_key_down(m, MLX_KEY_S));
		param->offset_x += 5 * (mlx_is_key_down(m, MLX_KEY_D));
	}
}
