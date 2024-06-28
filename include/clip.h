#ifndef CLIP_H
# define CLIP_H

#include "t_line.h"
#include "libft.h"
#include "interpolate_color.h"

extern int	clip(t_line *line, int xmax, int ymax);

typedef int	t_clip_code;

enum e_clip_code
{
	INSIDE = 0,
	LEFT = 1,
	RIGHT = 2,
	BOTTOM = 4,
	TOP = 8
};

#endif /* CLIP_H */
