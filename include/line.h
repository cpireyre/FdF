#ifndef LINE_H
# define LINE_H

#include <stdint.h>

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
}				t_line;

typedef struct	s_gradient
{
	uint32_t	start;
	uint32_t	curr;
	uint32_t	end;
	int			span;
	int			offset;
}				t_gradient;

#endif /* LINE_H */
