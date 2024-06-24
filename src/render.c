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

#include "render.h"

static void	render_frame(t_render_context *ctx);
void		move(mlx_t *m, t_projection *param);
static void	key_hook(mlx_key_data_t keydata, t_render_context *ctx);
static void	paint_background(mlx_image_t *image, uint32_t bgcolor);

void	render(t_render_context ctx, t_map *map)
{
	ctx.map = map;
	ctx.param.scale = 100;
	ctx.param.angle = 45;
	ctx.param.offset_x = (int)ctx.img->width / 3;
	ctx.param.offset_y = (int)ctx.img->height / 2;
	mlx_key_hook(ctx.mlx, (mlx_keyfunc)key_hook, &ctx);
	mlx_loop_hook(ctx.mlx, (t_hook)render_frame, &ctx);
	mlx_loop(ctx.mlx);
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
	paint_background(ctx->img, ctx->bg_color);
	ctx->rasterize(ctx->img, ctx->map);
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(ctx->mlx);
}
static void	paint_background(mlx_image_t *image, uint32_t bgcolor)
{
	int	i;
	int	j;

	i = 0;
	while ((uint32_t)i < image->width)
	{
		j = 0;
		while ((uint32_t)j < image->height)
		{
			mlx_put_pixel(image, (uint32_t)i, (uint32_t)j, bgcolor);
			j++;
		}
		i++;
	}
}
