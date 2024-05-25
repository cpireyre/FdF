#include <stdlib.h>

void	ft_memdel(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}
