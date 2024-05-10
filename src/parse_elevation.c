#include <stdlib.h>

int	**parse_elevation(char **lines)
{
	int	**elevation;
	size_t	i;

	i = 0;
	while (lines[i])
		i++;
	elevation = malloc(sizeof(int *) * 
}
