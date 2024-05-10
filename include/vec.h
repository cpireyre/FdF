#ifndef VEC_H
# define VEC_H

#define INITIAL_CAPACITY  42

typedef struct
{
	int	*d;
	size_t	size;
	size_t	capacity;
}	t_vec;

int	initvec(t_vec *v);
int	pushvec(t_vec *v, int k);

#endif
