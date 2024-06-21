/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:09:12 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/21 12:36:26 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "t_map.h"
#include "config.h"
#include "t_tuple.h"
#include "interpolate_color.h"

static int		point_is_in_window(t_point p, int width, int height);
static t_point	move_to_next(t_point p, int *err, t_tuple delta, t_tuple slope);

void	plot(mlx_image_t *img, t_point p, uint32_t color)
{
	if (point_is_in_window(p, WIN_WIDTH, WIN_HEIGHT))
		mlx_put_pixel(img, (uint32_t)p.pixel_x, (uint32_t)p.pixel_y, color);
}

void	bresenham(mlx_image_t *img, t_point begin, t_point end)
{
	int		err;
	int		steps;
	t_tuple	delta;
	t_tuple	slope;

	delta.x = ft_abs(end.pixel_x - begin.pixel_x);
	delta.y = -ft_abs(end.pixel_y - begin.pixel_y);
	err = delta.x + delta.y;
	steps = delta.x * (delta.x > -delta.y) - delta.y * (-delta.y >= delta.x);
	slope.x = (begin.pixel_x < end.pixel_x) - (begin.pixel_x >= end.pixel_x);
	slope.y = (begin.pixel_y < end.pixel_y) - (begin.pixel_y >= end.pixel_y);
	int i = 0;
	while (begin.pixel_x != end.pixel_x || begin.pixel_y != end.pixel_y)
	{
		plot(img, begin, interpolate_color(begin.color, end.color, i, steps));
		i++;
		begin = move_to_next(begin, &err, delta, slope);
	}
	plot(img, end, end.color);
}

static t_point	move_to_next(t_point p, int *err, t_tuple delta, t_tuple slope)
{
	int	double_err;

	double_err = *err * 2;
	if (double_err > delta.y)
	{
		p.pixel_x += slope.x;
		*err += delta.y;
	}
	if (double_err < delta.x)
	{
		p.pixel_y += slope.y;
		*err += delta.x;
	}
	return (p);
}

static int	point_is_in_window(t_point p, int width, int height)
{
	return (0 <= p.pixel_x && p.pixel_x < width
		&& 0 <= p.pixel_y && p.pixel_y < height);
}
