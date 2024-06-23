/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:43:04 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/21 10:03:55 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "t_map.h"
#include "config.h"
#include "render.h"
#include "rasterize.h"

static void	render_frame(t_render_context *ctx);
void		move(mlx_t *m, t_projection *param);
static void	key_hook(mlx_key_data_t keydata, t_render_context *ctx);

void	render(mlx_t *mlx, mlx_image_t *img, t_map *map)
{
	struct s_render_context	ctx;

	ctx.mlx = mlx;
	ctx.img = img;
	ctx.map = map;
	ctx.param.scale = 100;
	ctx.param.angle = 45;
	ctx.param.offset_x = WIN_WIDTH / 3;
	ctx.param.offset_y = WIN_HEIGHT / 2;
	mlx_key_hook(mlx, (mlx_keyfunc)key_hook, &ctx);
	mlx_loop_hook(mlx, (t_hook)render_frame, &ctx);
	mlx_loop(mlx);
}

static void	key_hook(mlx_key_data_t keydata, t_render_context *ctx)
{
	(void)keydata;
	(void)ctx;
}

static void	render_frame(t_render_context *ctx)
{
	move(ctx->mlx, &ctx->param);
	project(ctx->map, &ctx->param);
	paint_background(ctx->img, 0x40463aff);
	rasterize(ctx->img, ctx->map);
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(ctx->mlx);
}

