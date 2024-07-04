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
static void	plot(mlx_image_t *img, int *z_buffer, t_line *line, int i);

void	rasterize(mlx_image_t *image, int *z_buffer, t_line line)
{
	line.delta_x = ft_abs(line.screen1.x - line.screen0.x);
	line.delta_y = -ft_abs(line.screen1.y - line.screen0.y);
	line.slope_x = ft_sign(line.screen0.x, line.screen1.x);
	line.slope_y = ft_sign(line.screen0.y, line.screen1.y);
	line.length = ft_max(line.delta_x, -line.delta_y);
	if (line.length)
		line.z_dir = (int)round((line.world1.z - line.world0.z) /  line.length);
	else
		line.z_dir = 0;
	bresenham(image, z_buffer, line);
}

static void	bresenham(mlx_image_t *img, int *z_buffer, t_line line)
{
	int			i;
	int			err;
	int			double_err;

	i = 0;
	err = line.delta_x + line.delta_y;
	while (line.screen0.x != line.screen1.x || line.screen0.y != line.screen1.y)
	{
		double_err = err * 2;
		plot(img, z_buffer, &line, i);
		if (double_err > line.delta_y)
		{
			err += line.delta_y;
			line.screen0.x += line.slope_x;
		}
		if (double_err < line.delta_x)
		{
			err += line.delta_x;
			line.screen0.y += line.slope_y;
		}
		i++;
	}
	/*plot(img, z_buffer, &line, i);*/
	/*mlx_put_pixel(img, (uint32_t)line.screen1.x, (uint32_t)line.screen1.y, line.color1);*/
}

static void	plot(mlx_image_t *img, int *z_buffer, t_line *line, int i)
{
	uint32_t	color;
	int			*old_z;
	int			new_z;

	double lerp = (double)i / (double)line->length;
	color = (uint32_t)round(interpolate_color(line->color0, line->color1,
					lerp));
	new_z = (int)round(line->world0.z + i * line->z_dir);
	old_z = &z_buffer[(uint32_t)line->screen0.y * img->width + (uint32_t)line->screen0.x];
	if (new_z > *old_z)
	{
		*old_z = new_z;
		mlx_put_pixel(img, (uint32_t)line->screen0.x, (uint32_t)line->screen0.y,
				color);
	}
}
