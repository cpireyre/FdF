#ifndef CLIP_H
# define CLIP_H

# include "line.h"
# include "config.h"

extern int	clip(t_line *line);

typedef int	t_outcode;

enum e_outcode
{
	INSIDE = 0,
	LEFT = 1,
	RIGHT = 2,
	BOTTOM = 4,
	TOP = 8
};

int	clip(t_line *line);

struct s_line_d
{
	double x0;
	double y0;
	double x1;
	double y1;
};

#endif /* CLIP_H */
