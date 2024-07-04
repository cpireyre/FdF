/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:36:06 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/04 11:28:31 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rasterize.h"

static void		bresenham(mlx_image_t *img, int *z_buffer, t_line line);
static void	plot(mlx_image_t *img, t_v2i a, uint32_t color);
static int	occluded(int *z_buffer, uint32_t z_index, int z);

void	rasterize(mlx_image_t *image, int *z_buffer, t_line line)
{
	line.delta.x = ft_abs(line.screen1.x - line.screen0.x);
	line.delta.y = -ft_abs(line.screen1.y - line.screen0.y);
	line.length = ft_max(line.delta.x, -line.delta.y);
	if (line.length)
	{
		line.slope.x = ft_sign(line.screen0.x, line.screen1.x);
		line.slope.y = ft_sign(line.screen0.y, line.screen1.y);
		line.z_dir = (int)(line.world1.z - line.world0.z) / line.length;
		bresenham(image, z_buffer, line);
	}
}

static void	bresenham(mlx_image_t *img, int *z_buffer, t_line line)
{
	int			i;
	int			err;
	int			double_err;

	i = 0;
	err = line.delta.x + line.delta.y;
	while (line.screen0.x != line.screen1.x || line.screen0.y != line.screen1.y)
	{
		double_err = err * 2;
		double lerp = (double)i / (double)line.length;
		uint32_t color = interpolate_color(line.color0, line.color1, lerp);
		if (!occluded(z_buffer, (uint32_t)line.screen0.y * img->width + (uint32_t)line.screen0.x, (int)(line.world0.z + i * line.z_dir)))
			plot(img, line.screen0, color);
		if (double_err > line.delta.y)
		{
			err += line.delta.y;
			line.screen0.x += line.slope.x;
		}
		if (double_err < line.delta.x)
		{
			err += line.delta.x;
			line.screen0.y += line.slope.y;
		}
		i++;
	}
	if (!occluded(z_buffer, (uint32_t)(line.screen1.y * (int)img->width + line.screen1.x), (int)line.world1.z))
		plot(img, line.screen1, line.color1);
}

static int	occluded(int *z_buffer, uint32_t z_index, int z)
{
	int	*old_z;

	old_z = &z_buffer[z_index];
	if (z > *old_z)
	{
		*old_z = z;
		return (0);
	}
	return (1);
}

static void	plot(mlx_image_t *img, t_v2i a, uint32_t color)
{
	mlx_put_pixel(img, (uint32_t)a.x, (uint32_t)a.y, color);
}
