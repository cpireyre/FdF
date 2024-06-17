/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:10:25 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/14 13:07:56 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "t_map.h"
#include "config.h"

static void draw_line(mlx_image_t *img, t_point begin, t_point end);
int		point_is_in_window(t_point p, unsigned int width, unsigned int height);

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
	while (i + 1 < map->rows)
	{
		j = 0;
		while (j + 1 < map->cols)
		{
			curr = map->points[i][j];
			draw_line(img, map->points[i + 1][j], curr);
			draw_line(img, map->points[i][j + 1], curr);
			j++;
		}
		i++;
	}
}

int		point_is_in_window(t_point p, unsigned int width, unsigned int height)
{
	return (0 <= p.pixel_x && p.pixel_x < width
			&& 0 <= p.pixel_y && p.pixel_y < height);
}


/* TODO: do i need own abs(3)? */
static void draw_line(mlx_image_t *img, t_point begin, t_point end)
{
    int dx = abs((int)end.pixel_x - (int)begin.pixel_x);
    int dy = abs((int)end.pixel_y - (int)begin.pixel_y);
    int sx = (begin.pixel_x < end.pixel_x) ? 1 : -1;
    int sy = (begin.pixel_y < end.pixel_y) ? 1 : -1;
    int err = dx - dy;

    while (1)
	{
		if (point_is_in_window(begin, WIN_WIDTH, WIN_HEIGHT))
			mlx_put_pixel(img, begin.pixel_x, begin.pixel_y, 0xffffffff);
        if (begin.pixel_x == end.pixel_x
			&& begin.pixel_y == end.pixel_y)
			break;
        int e2 = 2 * err;
        if (e2 > -dy)
		{
            err -= dy;
            begin.pixel_x = (unsigned int)((int)begin.pixel_x + sx);
        }
        if (e2 < dx)
		{
            err += dx;
			begin.pixel_y = (unsigned int)((int)begin.pixel_y + sy);
        }
    }
}
