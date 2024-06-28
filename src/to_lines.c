#include "t_map.h"
#include "libft.h"
#include "line.h"
#include <stdlib.h>

static t_line	to_line(t_vector a, t_vector b);

int	to_lines(t_map *map, t_line **l, t_arena a)
{
	int			i;
	int			j;
	t_vector	curr;
	int			num_lines;
	int			k;
	t_line		*lines;

	num_lines = (map->rows - 1) * map->cols + (map->cols - 1) * map->rows;
	lines = arena_calloc(a, (size_t)num_lines, sizeof(t_line));
	if (!lines)
		return (-1);
	i = 0;
	k = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			curr = map->points[i][j];
			if (i + 1 < map->rows)
			{
				lines[k++] = to_line(curr, map->points[i + 1][j]);
			}
			if (j + 1 < map->cols)
			{
				lines[k++] = to_line(curr, map->points[i][j + 1]);
			}
			j++;
		}
		i++;
	}
	*l = lines;
	return (num_lines);
}

static t_line	to_line(t_vector a, t_vector b)
{
	t_line	line;

	line.x0 = a.x;
	line.y0 = a.y;
	line.x1 = b.x;
	line.y1 = b.y;
	line.z0 = a.z;
	line.z1 = b.z;
	line.color0 = (uint32_t)a.c;
	line.color1 = (uint32_t)b.c;
	return (line);
}

void	print_line(t_line line)
{
	ft_printf("(%d, %d, %d) -> (%d, %d, %d), ", line.x0, line.y0, line.z0, line.x1, line.y1, line.z1);
}

void	print_lines(t_line *lines, int num_lines)
{
	int	i;

	i = 0;
	while (i < num_lines)
	{
		print_line(lines[i]);
		i++;
	}
}
