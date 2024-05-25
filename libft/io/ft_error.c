#include <stdio.h>
#include <stdlib.h>

void	*ft_error(void *data, char *msg)
{
	free(data);
	perror(msg);
	return (NULL);
}
