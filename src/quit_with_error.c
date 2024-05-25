#include <stdio.h>
#include <stdlib.h>

void	*quit_with_error(void *data, const char *msg)
{
	free(data);
	perror(msg);
	return (NULL);
}
