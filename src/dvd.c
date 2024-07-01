#include "libft.h"
#include "transform.h"

void	dvd(t_transform *T, int width, int height)
{
	static t_vector	offset;
	static t_vector	direction;

	if (!direction.x)
		direction.x = 1;
	if (!direction.y)
		direction.y = 1;
	offset.x += direction.x;
	offset.y += direction.y;
	if (offset.x == width || offset.x == 0)
		direction.x *= -1;
	if (offset.y == height || offset.y == 0)
		direction.y *= -1;
	T->offset_x = offset.x;
	T->offset_y = offset.y;
}
