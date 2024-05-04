#include "vec.h"

int	vec_init(t_vec *v, size_t initial_capacity, size_t elem_size);
int	vec_push(t_vec *v, void *elem);
int	vec_resize(t_vec *v, size_t new_capacity);

int		vec_init(t_vec *v, size_t initial_capacity, size_t elem_size)
{
	v->capacity = initial_capacity;
	v->size = 0;
	v->elem_size = elem_size;
	v->data = malloc(v->elem_size * v->capacity);
	if (v->data)
		return (0);
	else
		return (1);
}

int		vec_push(t_vec *v, void *elem)
{
	int	ret;

	if (!elem)
		return (1);
	if (v->capacity == 0)
	{
		v->capacity = 1;
		v->data = malloc(v->elem_size * v->capacity);
		if (!v->data)
			return (1);
	}
	else if (v->size == v->capacity)
	{
		ret = vec_resize(v, 2 * v->capacity);
		if (ret)
			return (1);
	}
	ft_memcpy(v->data + (v->size * v->elem_size), elem, v->elem_size);
	v->size++;
	return (0);
}

int	vec_resize(t_vec *v, size_t new_capacity)
{
	void	*new_data;

	new_data = malloc(v->elem_size * new_capacity);
	if (!new_data)
		return (1);
	ft_memcpy(new_data, v->data, v->size * v->elem_size);
	free(v->data);
	v->data = new_data;
	v->capacity = new_capacity;
	return (0);
}

void		vec_free(t_vec *v)
{
	free(v->data);
	v->data = NULL;
}
