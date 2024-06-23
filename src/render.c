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

static void	loop_hook(void *param);
void		move(mlx_t *m, t_projection *param);
void		draw(t_render_context *ctx, t_map *map);
void		paint_background(mlx_image_t *img, uint32_t bgcolor);
void	plot(void *img, int x, int y, uint32_t color);
static void	key_hook(mlx_key_data_t keydata, void *param);

void	render(mlx_t *mlx, mlx_image_t *img, t_map *map)
{
	struct s_render_context	ctx;

	ctx.mlx = mlx;
	ctx.plot = &plot;
	ctx.quality = MEDIUM;
	ctx.img = img;
	ctx.map = map;
	ctx.param.scale = 100;
	ctx.param.angle = 45;
	ctx.param.offset_x = WIN_WIDTH / 3;
	ctx.param.offset_y = WIN_HEIGHT / 2;
	mlx_key_hook(mlx, &key_hook, &ctx);
	mlx_loop_hook(mlx, &loop_hook, &ctx);
	mlx_loop(mlx);
}

static void	key_hook(mlx_key_data_t keydata, void *param)
{
	struct s_render_context	*ctx;

	ctx = (struct s_render_context*)param;
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
	{
		ctx->quality = (ctx->quality + 1) % 2;
		ft_dprintf(2, "inc. qual is now: %d\n", ctx->quality);
	}
}

static void	loop_hook(void *render_context)
{
	t_render_context	*ctx;

	ctx = (t_render_context *)render_context;
	paint_background(ctx->img, 0x40463aff);
	move(ctx->mlx, &ctx->param);
	project(ctx->map, &ctx->param);
	draw(ctx, ctx->map);
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(ctx->mlx);
}

void	paint_background(mlx_image_t *img, uint32_t bgcolor)
{
	int	i;
	int	j;

	i = 0;
	while ((uint32_t)i < img->width)
	{
		j = 0;
		while ((uint32_t)j < img->height)
			mlx_put_pixel(img, (uint32_t)i, (uint32_t)j++, bgcolor);
		i++;
	}
}

void	plot(void *img, int x, int y, uint32_t color)
{
	int	point_is_in_window;

	point_is_in_window = 0 <= x && x < WIN_WIDTH && 0 <= y && y < WIN_HEIGHT;
	if (point_is_in_window)
		mlx_put_pixel((mlx_image_t*)img, (uint32_t)x, (uint32_t)y, color);
}

