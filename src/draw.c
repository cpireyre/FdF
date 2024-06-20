/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:10:25 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/20 13:56:39 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "t_map.h"
#include "config.h"

int			point_is_in_window(t_point p, int width, int height);
void		bresenham(mlx_image_t *img, t_point bgn, t_point end);
static void	draw_line(mlx_image_t *img, t_point begin, t_point end);

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

void	draw(mlx_image_t *img, t_map *map)
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
			if (i + 1 < map->rows)
				draw_line(img, curr, map->points[i + 1][j]);
			if (j + 1 < map->cols)
				draw_line(img, curr, map->points[i][j + 1]);
			j++;
		}
		i++;
	}
}

static void	draw_line(mlx_image_t *img, t_point begin, t_point end)
{
	bresenham(img, begin, end);
}
