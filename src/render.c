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

void	render(mlx_t *mlx, mlx_image_t *img, t_map *map)
{
	struct s_ptr	p;

	p.mlx = mlx;
	p.img = img;
	p.map = map;
	p.param.scale = 100;
	p.param.angle = 44.3F;
	p.param.offset_x = WIN_WIDTH / 3;
	p.param.offset_y = WIN_HEIGHT / 2;
	mlx_loop_hook(mlx, &loop_hook, &p);
	mlx_loop(mlx);
}

static void	loop_hook(void *ctx)
{
	struct s_ptr		*p;
	t_render_context	render_context;

	p = (struct s_ptr *)ctx;
	render_context.img = p->img;
	render_context.plot = &plot;
	paint_background(p->img, 0x40463aff);
	move(p->mlx, &p->param);
	project(p->map, &p->param);
	draw(&render_context, p->map);
	if (mlx_is_key_down(p->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(p->mlx);
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

static int		point_is_in_window(int x, int y, int width, int height);

static int	point_is_in_window(int x, int y, int width, int height)
{
	return (0 <= x && x < width && 0 <= y && y < height);
}

void	plot(void *img, int x, int y, uint32_t color)
{
	if (point_is_in_window(x, y, WIN_WIDTH, WIN_HEIGHT))
		mlx_put_pixel((mlx_image_t*)img, (uint32_t)x, (uint32_t)y, color);
}

