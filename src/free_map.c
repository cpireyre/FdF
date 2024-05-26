#include <stdlib.h>
#include "t_map.h"

void	free_map(t_map *map)
{
	while (map->rows--)
		free(map->points[map->rows]);
	free(map->points);
}
