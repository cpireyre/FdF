/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_lines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:33:57 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/05 09:54:40 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_line	to_line(t_v4i a, t_v4i b);
static void		find_min_max_elevation(t_map *map, int *min, int *max);

int	to_lines(t_map *map, t_line **l, t_arena a)
{
	t_v4i	curr;
	int		num_lines;
	t_line	*lines;
	t_v4i	inc;

	num_lines = (map->rows - 1) * map->cols + (map->cols - 1) * map->rows;
	lines = arena_calloc(a, (size_t)num_lines, sizeof(t_line));
	if (!lines)
		return (0);
	inc.x = -1;
	inc.z = 0;
	while (++inc.x < map->rows)
	{
		inc.y = -1;
		while (++inc.y < map->cols)
		{
			curr = map->points[inc.x][inc.y];
			if (inc.x + 1 < map->rows)
				lines[inc.z++] = to_line(curr, map->points[inc.x + 1][inc.y]);
			if (inc.y + 1 < map->cols)
				lines[inc.z++] = to_line(curr, map->points[inc.x][inc.y + 1]);
		}
	}
	*l = lines;
	return (num_lines);
}

static t_line	to_line(t_v4i a, t_v4i b)
{
	t_line	line;

	line.world0.x = a.x;
	line.world0.y = a.y;
	line.world0.z = a.z;
	line.world1.x = b.x;
	line.world1.y = b.y;
	line.world1.z = b.z;
	line.color0 = (uint32_t)a.c;
	line.color1 = (uint32_t)b.c;
	return (line);
}

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
			map->points[i][j].c = (int)interpolate_color(
					(uint32_t)low_color, (uint32_t)high_color,
					(double)map->points[i][j].z / (double)(max - min));
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
	*min = map->points[0][0].z;
	*max = *min;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (*min > map->points[i][j].z)
				*min = map->points[i][j].z;
			if (*max < map->points[i][j].z)
				*max = map->points[i][j].z;
			j++;
		}
		i++;
	}
}
