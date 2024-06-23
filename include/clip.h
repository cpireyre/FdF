#ifndef CLIP_H
# define CLIP_H

# include <math.h>
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

#endif /* CLIP_H */
