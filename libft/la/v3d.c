#include "ft_la.h"

t_v3d	v3d_add(t_v3d a, t_v3d b)
{
	t_v3d	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_v3d	v3dd(double x)
{
	t_v3d	result;
	
	result.x = x;
	result.y = x;
	result.z = x;
	return (result);
}

t_v3d	v3d_div(t_v3d a, t_v3d b)
{
	t_v3d	result;

	result.x = a.x / b.x;
	result.y = a.y / b.y;
	result.z = a.z / b.z;
	return (result);
}

t_v3d	v3d_mul(t_v3d a, t_v3d b)
{
	t_v3d	result;

	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	return (result);
}
