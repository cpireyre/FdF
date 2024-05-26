#include <stdio.h>
#include <stdlib.h>

int	ft_error(void *data, char *msg)
{
	free(data);
	perror(msg);
	return (1);
}
