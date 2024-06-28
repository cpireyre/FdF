#include "t_map.h"
#include "libft.h"
#include "line.h"
#include <stdlib.h>

static t_line	to_line(t_vector a, int x1, int y1);

int	to_lines(t_map *map, t_line **l)
{
	int			i;
	int			j;
	t_vector	curr;
	int			num_lines;
	int			k;
	t_line		*lines;

	num_lines = (map->rows - 1) * map->cols + (map->cols - 1) * map->rows;
	lines = malloc(sizeof(t_line) * (size_t)num_lines);
	if (!lines)
		return (-1);
	i = 0;
	k = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			curr = ft_vec2(i, j);
			if (i + 1 < map->rows)
			{
				lines[k++] = to_line(curr, i + 1, j);
			}
			if (j + 1 < map->cols)
			{
				lines[k++] = to_line(curr, i, j + 1);
			}
			j++;
		}
		i++;
	}
	*l = lines;
	return (num_lines);
}

static t_line	to_line(t_vector a, int x1, int y1)
{
	t_line	line;

	line.x0 = a.x;
	line.y0 = a.y;
	line.x1 = x1;
	line.y1 = y1;
	return (line);
}

void	print_lines(t_line *lines, int num_lines)
{
	int	i;

	i = 0;
	while (i < num_lines)
	{
		ft_printf("(%d, %d) -> (%d, %d), ", lines[i].x0, lines[i].y0, lines[i].x1, lines[i].y1);
		i++;
	}
}
