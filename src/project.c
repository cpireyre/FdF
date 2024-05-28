/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:21:31 by copireyr          #+#    #+#             */
/*   Updated: 2024/05/28 11:09:46 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_map.h"
#include <math.h>

static t_point	project_point(t_point p, t_projection *s, int x, int y);

void	project(t_map *map, t_projection *param)
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
			map->points[i][j] = project_point(curr, param, i, j);
			j++;
		}
		i++;
	}
}

static t_point	project_point(t_point p, t_projection *s, int x, int y)
{
	t_point	pro;
	double	iso_x;
	double	iso_y;

	iso_x = (x - y) * cos(45);
	iso_y = (x + y) * sin(45) / 2 - p.elevation;
	pro.pixel_x = s->offset_x + (unsigned int)(s->scale * iso_x);
	pro.pixel_y = s->offset_y + (unsigned int)(s->scale * iso_y);
	return (pro);
}
