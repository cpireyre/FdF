#include "ft_la.h"

t_v2i v2i3d(t_v3d a)
{
	t_v2i	result;

	result.x = (int)a.x;
	result.y = (int)a.y;
	return (result);
}
