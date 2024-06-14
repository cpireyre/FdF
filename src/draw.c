/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:10:25 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/14 10:13:11 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_map.h"

void	draw_points(mlx_image_t *img, t_map *map)
{
	int		i;
	int		j;
	t_point	curr;

	i = 0;
	while ((uint32_t)i < img->width)
	{
		j = 0;
		while ((uint32_t)j < img->height)
			mlx_put_pixel(img, (uint32_t)i, (uint32_t)j++, 0x000000ff);
		i++;
	}
	i = 0;
	while (i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			curr = map->points[i][j];
			if (0 <= curr.pixel_x && curr.pixel_x < img->width
				&& 0 <= curr.pixel_y && curr.pixel_y < img->height)
				mlx_put_pixel(img, curr.pixel_x, curr.pixel_y, 0xffffffff);
		}
		i++;
	}
}
