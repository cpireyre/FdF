/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:36:06 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/28 11:40:32 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rasterize.h"
#include "libft.h"

static void		bresenham(mlx_image_t *img, t_line line);
static uint32_t	lerp(uint32_t color0, uint32_t color1, int i, int steps);

void	rasterize(mlx_image_t *image, t_line line)
{
	t_line	orig;
	double	original_length;
	double	ratio0;
	double	ratio1;

	orig= line;
	original_length = ft_distance(line.x0, line.y0, line.x1, line.y1);
	if (clip(&line, (int)image->width, (int)image->height))
	{
		ratio0 = ft_distance(orig.x0, orig.y0, line.x0, line.y0) / original_length;
		ratio1 = ft_distance(orig.x1, orig.y1, line.x1, line.y1) / original_length;
		line.color0 = interpolate_color((uint32_t)orig.color0, (uint32_t)orig.color1, ratio0);
		line.color1 = interpolate_color((uint32_t)orig.color0, (uint32_t)orig.color1, ratio1);
		line.delta_x = ft_abs(line.x1 - line.x0);
		line.delta_y = -ft_abs(line.y1 - line.y0);
		line.slope_x = ft_sign(line.x0, line.x1);
		line.slope_y = ft_sign(line.y0, line.y1);
		line.length = ft_max(line.delta_x, -line.delta_y);
		bresenham(image, line);
	}
}

static void	bresenham(mlx_image_t *img, t_line line)
{
	int			i;
	int			err;
	uint32_t	color;
	int			double_err;

	i = 0;
	err = line.delta_x + line.delta_y;
	while (line.x0 != line.x1 || line.y0 != line.y1)
	{
		double_err = err * 2;
		mlx_put_pixel(img, (uint32_t)line.x0, (uint32_t)line.y0, color);
		color = lerp(line.color0, line.color1, i, line.length);
		if (double_err > line.delta_y)
		{
			err += line.delta_y;
			line.x0 += line.slope_x;
		}
		if (double_err < line.delta_x)
		{
			err += line.delta_x;
			line.y0 += line.slope_y;
		}
		i++;
	}
	mlx_put_pixel(img, (uint32_t)line.x1, (uint32_t)line.y1, line.color1);
}

static uint32_t	lerp(uint32_t color0, uint32_t color1, int i, int steps)
{
	return ((uint32_t)round(interpolate_color(color0, color1,
				(double) i / (double)steps)));
}
