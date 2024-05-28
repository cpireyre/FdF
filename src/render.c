/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:43:04 by copireyr          #+#    #+#             */
/*   Updated: 2024/05/28 11:10:24 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "libft.h"
#include "t_map.h"
#include "config.h"
#include <string.h>

static void			key_hooks(mlx_key_data_t key_data, void *param);
static void			draw_points(mlx_image_t *img, t_map *map);
static t_projection	init_projection(void);

int	render(t_map *map, const char *name)
{
	mlx_t			*mlx;
	t_projection	param;
	mlx_image_t		*img;

	mlx_set_setting(MLX_HEADLESS, false);
	mlx = mlx_init(WIDTH, HEIGHT, name, false);
	if (!mlx)
		return (1);
	mlx_key_hook(mlx, &key_hooks, mlx);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
	{
		ft_printf("Uh oh no image");
		return (1);
	}
	param = init_projection();
	project(map, &param);
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		return (1);
	draw_points(img, map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (MLX_SUCCESS);
}

static void	key_hooks(mlx_key_data_t key_data, void *param)
{
	if (key_data.key == MLX_KEY_ESCAPE)
		mlx_close_window((mlx_t *)param);
}

static void	draw_points(mlx_image_t *img, t_map *map)
{
	int		i;
	int		j;
	t_point	curr;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			curr = map->points[i][j];
			mlx_put_pixel(img, curr.pixel_x, curr.pixel_y, 0x0000ffff);
			j++;
		}
		i++;
	}
}

static t_projection	init_projection(void)
{
	t_projection	param;

	param.scale = 30;
	param.angle = (float)0.70710678118;
	param.offset_x = WIDTH / 3;
	param.offset_y = HEIGHT / 3;
	return (param);
}
