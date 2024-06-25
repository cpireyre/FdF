/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:45:09 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/21 11:30:45 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_render_context	initialize_ctx(const char *name, int width, int height);
static void	render_frame(t_render_context *ctx);
void		move(mlx_t *m, t_projection *param);

int	main(int argc, char **argv)
{
	int						err;
	t_map					map;
	t_arena					a;
	t_render_context		ctx;

	if (argc == 2)
	{
		a = arena_new();
		if (!a)
			return (1);
		err = build_map_from_file(argv[1], &map, a);
		ctx = initialize_ctx(argv[1], WIN_WIDTH, WIN_HEIGHT);
		if (!err && ctx.init_success)
		{
			assign_colors(&map, LOW_COLOR, HIGH_COLOR);
			ctx.map = &map;
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
	ctx.image_size_in_bytes = ctx.img->width * ctx.img->height * 4;
	if (mlx_image_to_window(ctx.mlx, ctx.img, 0, 0) != -1)
		ctx.init_success = 1;
	return (ctx);
}

static void	render_frame(t_render_context *ctx)
{
    ft_memset_32(ctx->img->pixels, ctx->bg_color, ctx->image_size_in_bytes);
	move(ctx->mlx, &ctx->param);
	project(ctx->map, &ctx->param);
	rasterize(ctx->img, ctx->map);
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(ctx->mlx);
}
