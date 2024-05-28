/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:43:04 by copireyr          #+#    #+#             */
/*   Updated: 2024/05/28 15:35:42 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "t_map.h"
#include "config.h"
#include <string.h>

static void			key_hooks(void *p);
static void			draw_points(mlx_image_t *img, t_map *map);
static t_projection	init_projection(void);
static void			actual_render(void *ptr);

int	render(t_map *map, const char *name)
{
	mlx_t			*mlx;
	t_projection	param;
	mlx_image_t		*img;
	struct s_ptr	p;

	mlx_set_setting(MLX_HEADLESS, false);
	mlx = mlx_init(WIDTH, HEIGHT, name, false);
	if (!mlx)
		return (1);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	param = init_projection();
	project(map, &param);
	draw_points(img, map);
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		return (1);
	p.mlx = mlx;
	p.img = img;
	p.map = map;
	p.param = &param;
	mlx_loop_hook(mlx, &key_hooks, &p);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	(void)actual_render;
	return (MLX_SUCCESS);
}

static void	actual_render(void *ptr)
{
	struct s_ptr	*p;

	p = (struct s_ptr *)ptr;
}

static void	key_hooks(void *ptr)
{
	struct s_ptr	*p;

	p = (struct s_ptr *)ptr;
	if (mlx_is_key_down(p->mlx, MLX_KEY_H))
		p->param->offset_x -= 1;
	if (mlx_is_key_down(p->mlx, MLX_KEY_L))
		p->param->offset_x += 1;
	if (mlx_is_key_down(p->mlx, MLX_KEY_J))
		p->param->offset_y += 1;
	if (mlx_is_key_down(p->mlx, MLX_KEY_K))
		p->param->offset_y -= 1;
	if (mlx_is_key_down(p->mlx, MLX_KEY_K)
		&& mlx_is_key_down(p->mlx, MLX_KEY_LEFT_SHIFT))
	{
		p->param->scale += 1;
	}
	if (mlx_is_key_down(p->mlx, MLX_KEY_J)
		&& mlx_is_key_down(p->mlx, MLX_KEY_LEFT_SHIFT))
	{
		p->param->scale -= 1;
		if (p->param->scale == 0)
			p->param->scale = 1;
	}
	project(p->map, p->param);
	draw_points(p->img, p->map);
	mlx_image_to_window(p->mlx, p->img, 0, 0);
	if (mlx_is_key_down(p->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(p->mlx);
}

static void	draw_points(mlx_image_t *img, t_map *map)
{
	int		i;
	int		j;
	t_point	curr;

	i = 0;
	while ((uint32_t)i < img->width)
	{
		j = 0;
		while ((uint32_t)j < img->height)
		{
			mlx_put_pixel(img, (uint32_t)i, (uint32_t)j, 0x000000ff);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			curr = map->points[i][j];
			if (0 <= curr.pixel_x && curr.pixel_x < img->width
				&& 0 <= curr.pixel_y && curr.pixel_y < img->height)
				mlx_put_pixel(img, curr.pixel_x, curr.pixel_y, 0xffffffff);
			j++;
		}
		i++;
	}
}

static t_projection	init_projection(void)
{
	t_projection	param;

	param.scale = 30;
	param.angle = 45;
	param.offset_x = WIDTH / 3;
	param.offset_y = HEIGHT / 3;
	return (param);
}
