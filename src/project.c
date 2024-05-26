#include "t_map.h"
#include <math.h>

static t_point	project_point(t_point p, t_projection *param, size_t x, size_t y);
void	project(t_map *map, t_projection *param)
{
	size_t	i;
	size_t	j;
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

static t_point	project_point(t_point p, t_projection *param, size_t x, size_t y)
{
	t_point	pro;
    double	cos_45 = cos(45);
    double	sin_45 = sin(45);

    double isoX = (x - y) * cos_45;
    double isoY = (x + y) * sin_45 / 2 - p.elevation;
    pro.pixelX = param->offset_x + (unsigned int)(param->scale * isoX);
    pro.pixelY = param->offset_y + (unsigned int)(param->scale * isoY);
	return (pro);
}
