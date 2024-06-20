/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:09:12 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/20 13:31:28 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_map.h"
#include "config.h"
#include "t_tuple.h"
#include "interpolate_colors.h"

static int	ft_abs(int a);
static int	point_is_in_window(t_point p, int width, int height);

void	plot(mlx_image_t *img, t_point p, uint32_t color)
{
	if (point_is_in_window(p, WIN_WIDTH, WIN_HEIGHT))
		mlx_put_pixel(img, (uint32_t)p.pixel_x, (uint32_t)p.pixel_y, color);
}

#include <stdio.h>
void	bresenham(mlx_image_t *img, t_point begin, t_point end)
{
	int		err;
	int		steps;
	t_tuple	delta;
	t_tuple	slope;
	int		float_err;

	delta.x = ft_abs(end.pixel_x - begin.pixel_x);
	delta.y = -ft_abs(end.pixel_y - begin.pixel_y);
	err = delta.x + delta.y;
	steps = delta.x * (delta.x > -delta.y) - delta.y * (-delta.y >= delta.x);
	slope.x = (begin.pixel_x < end.pixel_x) - (begin.pixel_x >= end.pixel_x);
	slope.y = (begin.pixel_y < end.pixel_y) - (begin.pixel_y >= end.pixel_y);
	if (begin.elevation == 0)
		begin.color = 0xa6e36dff;
	else
		begin.color = 0xe3896dff;
	if (end.elevation == 0)
		end.color = 0xa6e36dff;
	else
		end.color = 0xe3896dff;
	int	i = 0;
	while (i < steps)
	{
		uint32_t color = interpolate_color(begin.color, end.color, i, steps);
		plot(img, begin, color);
		float_err = 2 * err;
		if (float_err > delta.y)
		{
			begin.pixel_x += slope.x;
			err += delta.y;
		}
		if (float_err < delta.x)
		{
			begin.pixel_y += slope.y;
			err += delta.x;
		}
		i++;
	}
	plot(img, begin, 0x000000ff);
}

static int	ft_abs(int a)
{
	return ((a < 0) * -a + (a >= 0) * a);
}

static int	point_is_in_window(t_point p, int width, int height)
{
	return (0 <= p.pixel_x && p.pixel_x < width
		&& 0 <= p.pixel_y && p.pixel_y < height);
}
