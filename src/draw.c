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
#include <math.h>
#include "t_map.h"
#include "config.h"

static void draw_line(mlx_image_t *img, t_point begin, t_point end);
int		point_is_in_window(t_point p, int width, int height);

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

int		point_is_in_window(t_point p, int width, int height)
{
	return (0 <= p.pixel_x && p.pixel_x < width
			&& 0 <= p.pixel_y && p.pixel_y < height);
}


/* TODO: do i need own abs(3)? */
/* TODO: could optimise straight lines */ 
static void draw_line(mlx_image_t *img, t_point begin, t_point end)
{
    int dx = abs(end.pixel_x - begin.pixel_x);
    int dy = abs(end.pixel_y - begin.pixel_y);
    int sx = (begin.pixel_x < end.pixel_x) ? 1 : -1;
    int sy = (begin.pixel_y < end.pixel_y) ? 1 : -1;
    int err = dx - dy;

    while (1)
	{
		if (point_is_in_window(begin, WIN_WIDTH, WIN_HEIGHT))
			mlx_put_pixel(img,\
					(unsigned int)begin.pixel_x, (unsigned int)begin.pixel_y,\
					0xff00ffff);
        if (begin.pixel_x == end.pixel_x && begin.pixel_y == end.pixel_y)
			break ;
        int e2 = 2 * err;
        if (e2 > -dy)
		{
            err -= dy;
            begin.pixel_x += sx;
        }
        if (e2 < dx)
		{
            err += dx;
			begin.pixel_y += sy;
        }
    }
	/* // distance between points */
	/* double	ratio; */
	/* // differences */
	/* double	deltaX; */
	/* double	deltaY; */
	/* // current values */
	/* double	x; */
	/* double	y; */
	/* // distance step by step */
	/* double	i = 0; */

	/* // btoh of them outside the screen */
	/* if ((begin.pixel_x < 0 && end.pixel_x < 0) || (begin.pixel_y < 0 && end.pixel_y < 0) */
	/* 	|| (begin.pixel_x > WIN_WIDTH && end.pixel_x > WIN_WIDTH) || (begin.pixel_y > WIN_HEIGHT && end.pixel_y > WIN_HEIGHT)) */
	/* 	return; */
	/* // pythagorian theorem */
	/* ratio = sqrt(pow(end.pixel_x - begin.pixel_x, 2) + pow(end.pixel_y - begin.pixel_y, 2)); */
	/* deltaX = (end.pixel_x - begin.pixel_x) / ratio; */
	/* deltaY = (end.pixel_y - begin.pixel_y) / ratio; */
	/* // initial values */
	/* x = begin.pixel_x; */
	/* y = begin.pixel_y; */
	/* // do the distance step by step */
	/* while (i < ratio) */
	/* { */
	/* 	// if the current pixel is in the screen */
	/* 	if (x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT) */
	/* 		mlx_put_pixel(img, (uint32_t)round(x), (uint32_t)round(y), 0xffffffff); */
	/* 	// move the values enough and step one off the distance */
	/* 	x += deltaX; */
	/* 	y += deltaY; */
	/* 	i++; */
	/* } */
}
