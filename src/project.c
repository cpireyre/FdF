/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:21:31 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/20 13:58:21 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_map.h"
#include <math.h>

static t_vector	project_point(t_vector p, t_projection *s, int x, int y);

void	project(t_map *map, t_projection *param)
{
	int		i;
	int		j;
	t_vector	curr;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			curr = map->points[i][j];
			map->points[i][j] = project_point(curr, param, j, i);
			j++;
		}
		i++;
	}
}

/* TODO: benchmark using floats and precomputing sin and cos */
static t_vector	project_point(t_vector p, t_projection *s, int x, int y)
{
	double	iso_x;
	double	iso_y;
	double	scaled_iso_x;
	double	scaled_iso_y;

	iso_x = (x - y) * cos(s->angle);
	iso_y = (x + y) * sin(s->angle) - p.z;
	scaled_iso_x = s->scale * iso_x;
	scaled_iso_y = s->scale * iso_y;
	p.x = s->offset_x + (int)round(scaled_iso_x);
	p.y = s->offset_y + (int)round(scaled_iso_y);
	return (p);
}
