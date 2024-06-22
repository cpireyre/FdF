#ifndef DRAW_H
# define DRAW_H

#include <stdint.h>

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
}				t_line;

typedef int	t_outcode;

typedef struct	s_gradient
{
	uint32_t	start;
	uint32_t	end;
}				t_gradient;

enum e_outcode
{
	INSIDE = 0,
	LEFT = 1,
	RIGHT = 2,
	BOTTOM = 4,
	TOP = 8
};

int	clip(t_line *line);

#endif /* DRAW_H */
