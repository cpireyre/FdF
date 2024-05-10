#ifndef READ_ELEVATION_H
# define READ_ELEVATION_H

#include "vec.h"

typedef struct
{
	t_vec	v;
	size_t	rows;
	size_t	cols;
}	t_matrix;

int	read_elevation(const char *path, t_matrix *m);

#endif
