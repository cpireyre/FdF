#ifndef LINE_H
# define LINE_H

# include <stdint.h>
# include <math.h>

typedef struct s_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	int			length;
	int			delta_x;
	int			delta_y;
	int			slope_x;
	int			slope_y;
	uint32_t	color0;
	uint32_t	color1;
}				t_line;

typedef struct s_vec2
{
	int	x;
	int	y;
}				t_vec2;

extern int	clip(t_line *line, int xmax, int ymax);

typedef int	t_outcode;

enum e_outcode
{
	INSIDE = 0,
	LEFT = 1,
	RIGHT = 2,
	BOTTOM = 4,
	TOP = 8
};

#endif /* LINE_H */
