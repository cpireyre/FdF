#include <stdlib.h>
#include "libft.h"
#include "vec.h"

static int	resizevec(t_vec *v);

int	initvec(t_vec *v)
{
	v->d = malloc(sizeof(int) * INITIAL_CAPACITY);
	if (!v->d)
		return (1);
	v->size = 0;
	v->capacity = INITIAL_CAPACITY;
	return (0);
}

int	pushvec(t_vec *v, int k)
{
	if (v->size == v->capacity)
		if (resizevec(v))
			return (1);
	v->d[v->size] = k;
	v->size++;
	return (0);
}

static int	resizevec(t_vec *v)
{
	void	*new_data;
	void	*old_data;

	old_data = v->d;
	v->capacity *= 2;
	new_data = malloc(sizeof(int) * v->capacity);
	if (!new_data)
		return (1);
	v->d = ft_memcpy(new_data, old_data, sizeof(int) * v->size);
	free(old_data);
	return (0);
}
