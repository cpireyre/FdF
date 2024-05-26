#ifndef T_MAP_H
# define T_MAP_H

#include <stddef.h>

typedef struct
{
    int				elevation;
    unsigned int	pixelX;
    unsigned int	pixelY;
    unsigned int	color;
}	t_point;

typedef struct
{
    t_point	**points;
    size_t	rows;
    size_t	cols;
}	t_map;

typedef struct
{
	float			scale;
	float			angle;
	unsigned int	offset_x;
	unsigned int	offset_y;
}	t_projection;

void	free_map(t_map *map);
void	project(t_map *map, t_projection *param);

#endif /* T_MAP_H */
