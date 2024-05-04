#ifndef VEC_H
# define VEC_H

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

typedef struct
{
	char	*data;
	size_t	size;
	size_t	capacity;
	size_t	elem_size;
}	t_vec;

/* vec_init & resize always allocate, return 1 on error. */
int	vec_init(t_vec *v, size_t initial_capacity, size_t elem_size);
int	vec_resize(t_vec *v, size_t new_capacity);

/* vec_push may also allocate if resizing occurs. */
int	vec_push(t_vec *v, void *elem);

void	vec_free(t_vec *v);

#endif
