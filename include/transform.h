#ifndef TRANSFORM_H
# define TRANSFORM_H

#include "t_line.h"
#include "libft.h"
#include <math.h>
#define COS45 0.7071067812
#define SIN45 0.7071067812

typedef struct s_projection
{
	double	scale;
	double	angle;
	int		offset_x;
	int		offset_y;
}	t_projection;

t_line	project_line(t_line line, t_projection *s);

#endif /* TRANSFORM_H */
