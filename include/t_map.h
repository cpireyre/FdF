#ifndef T_MAP_H
# define T_MAP_H

typedef struct
{
    int				elevation;
    int				pixelX;
    int				pixelY;
    unsigned int	color;
}	t_point;

typedef struct
{
    t_point	**points;
    size_t	rows;
    size_t	cols;
}	t_map;

void	free_map(t_map *map);

#endif /* T_MAP_H */
