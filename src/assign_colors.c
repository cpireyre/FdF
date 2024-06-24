/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:45:05 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/21 11:12:18 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_map.h"
#include "rasterize.h"

static void	find_min_max_elevation(t_map *map, int *min, int *max);

void	assign_colors(t_map *map, uint32_t low_color, uint32_t high_color)
{
	int		i;
	int		j;
	int		min;
	int		max;

	i = 0;
	find_min_max_elevation(map, &min, &max);
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			map->points[i][j].color = interpolate_color( 
					(uint32_t)low_color, (uint32_t)high_color,
					map->points[i][j].elevation, max - min);
			j++;
		}
		i++;
	}
}

static void	find_min_max_elevation(t_map *map, int *min, int *max)
{
	int	i;
	int	j;

	i = 0;
	*min = map->points[0][0].elevation;
	*max = *min;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (*min > map->points[i][j].elevation)
				*min = map->points[i][j].elevation;
			if (*max < map->points[i][j].elevation)
				*max = map->points[i][j].elevation;
			j++;
		}
		i++;
	}
}
