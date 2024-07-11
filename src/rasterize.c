/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:36:06 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/11 11:43:06 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rasterize.h"

static void		bresenham(mlx_image_t *img, int *z_buffer, t_line line);
static void		plot(mlx_image_t *img, t_v2i a, uint32_t color);
static int		occluded(int *z_buffer, uint32_t z_index, double z);
static uint32_t	ft_index(uint32_t width, t_v2i pixel);

void	rasterize(mlx_image_t *image, int *z_buffer, t_line line)
{
	double	line_length;

	line.delta.x = ft_abs(line.screen1.x - line.screen0.x);
	line.delta.y = -ft_abs(line.screen1.y - line.screen0.y);
	line_length = ft_max(line.delta.x, -line.delta.y);
	if (line_length > 0)
	{
		line.slope.x = ft_sign(line.screen0.x, line.screen1.x);
		line.slope.y = ft_sign(line.screen0.y, line.screen1.y);
		line.z_dir = (int)(line.world1.z - line.world0.z) / (int)line_length;
		line.step = 1 / line_length;
		bresenham(image, z_buffer, line);
	}
}

/* evil branchless bresenham but CPU misprediction is real probably */
static void	bresenham(mlx_image_t *img, int *z_buffer, t_line line)
{
	int			i;
	int			err;
	double		current_z;
	uint32_t	color;

	err = line.delta.x + line.delta.y;
	i = 0;
	while (line.screen0.x != line.screen1.x || line.screen0.y != line.screen1.y)
	{
		color = interpolate_color(line.color0, line.color1, i * line.step);
		current_z = line.world0.z + i * line.z_dir;
		if (!occluded(z_buffer, ft_index(img->width, line.screen0), current_z))
			plot(img, line.screen0, color);
		line.screen0.x += line.slope.x * ((2 * err) > line.delta.y);
		line.screen0.y += line.slope.y * ((2 * err) < line.delta.x);
		err += line.delta.y * ((2 * err) > line.delta.y)
			+ line.delta.x * ((2 * err) < line.delta.x);
		i++;
	}
	if (!occluded(z_buffer, ft_index(img->width, line.screen1), line.world1.z))
		plot(img, line.screen1, line.color1);
}

static int	occluded(int *z_buffer, uint32_t z_index, double z)
{
	int	*old_z;

	old_z = &z_buffer[z_index];
	if (z > *old_z)
	{
		*old_z = (int)z;
		return (0);
	}
	return (1);
}

static void	plot(mlx_image_t *img, t_v2i a, uint32_t color)
{
	mlx_put_pixel(img, (uint32_t)a.x, (uint32_t)a.y, color);
}

static uint32_t	ft_index(uint32_t width, t_v2i pixel)
{
	return (width * (uint32_t)pixel.y + (uint32_t)pixel.x);
}
