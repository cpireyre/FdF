#ifndef LINE_H
# define LINE_H

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

#endif /* LINE_H */
