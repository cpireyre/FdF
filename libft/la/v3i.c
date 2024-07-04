#include "ft_la.h"

t_v3i	v3i(int x, int y, int z)
{
	t_v3i	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

t_v3i	v3i_add(t_v3i a, t_v3i b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}
