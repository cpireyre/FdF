#include "drawline.h"

void	bresenham(mlx_image_t *img, t_line line)
{
	int			i;
	int			err;
	uint32_t	color;
	int			double_err;

	err = line.delta_x + line.delta_y;
	i = 0;
	color = line.color0;
	while (i < line.length)
	{
		mlx_put_pixel(img, (uint32_t)line.x0, (uint32_t)line.y0, color);
		color = interpolate_color(line.color0, line.color1, ++i, line.length);
		double_err = err * 2;
		if (double_err > line.delta_y)
		{
			line.x0 += line.slope_x;
			err += line.delta_y;
		}
		if (double_err < line.delta_x)
		{
			line.y0 += line.slope_y;
			err += line.delta_x;
		}
	}
	mlx_put_pixel(img, (uint32_t)line.x1, (uint32_t)line.y1, line.color1);
}

static t_outcode	compute_outcode(int x, int y);
static void			clamp(t_line *l, int *x0, int *y0, t_outcode code);

/* Cohen–Sutherland line clip */
/* https://en.wikipedia.org/wiki/Cohen–Sutherland_algorithm */

int clip(t_line *line)
{
	t_outcode code0;
	t_outcode code1;

	code0 = compute_outcode(line->x0, line->y0);
	code1 = compute_outcode(line->x1, line->y1);
	if (!(code0 | code1))
		return (1);
	else if (code0 & code1)
		return (0);
	if (code0 > code1)
		clamp(line, &line->x0, &line->y0, code0);
	else
		clamp(line, &line->x1, &line->y1, code1);
	return (clip(line));
}

static t_outcode	compute_outcode(int x, int y)
{
	t_outcode	code;

	code = INSIDE;
	if (x < 0)
		code |= LEFT;
	else if (x >= WIN_WIDTH)
		code |= RIGHT;
	if (y < 0)
		code |= TOP;
	else if (y >= WIN_HEIGHT)
		code |= BOTTOM;
	return (code);
}

static void	clamp(t_line *l, int *x0, int *y0, t_outcode code)
{
	double	slope;

	slope = (double)(l->y1 - l->y0) / (double)(l->x1 - l->x0);
	if (code & TOP)
	{
		*x0 = l->x0 - (int)round(l->y0 / slope);
		*y0 = 0;
	}
	else if (code & BOTTOM)
	{
		*x0 = l->x0 + (int)round((WIN_HEIGHT - l->y0) / slope);
		*y0 = WIN_HEIGHT - 1;
	}
	else if (code & RIGHT)
	{
		*y0 = l->y0 + (int)round(slope * (WIN_WIDTH - l->x0));
		*x0 = WIN_WIDTH - 1;
	}
	else if (code & LEFT)
	{
		*y0 = l->y0 - (int)round(slope * l->x0);
		*x0 = 0;
	}
}

#include "interpolate_color.h"
#include "libft.h"
#include <math.h>

static uint32_t	color_to_int(t_color c);
static t_color	int_to_color(uint32_t i);
static uint8_t	interpolate_component(uint8_t s, uint8_t e, int cur, int steps);

uint32_t	interpolate_color(uint32_t start, uint32_t end, int curr, int steps)
{
	t_color	s;
	t_color	e;
	t_color	ret;

	if (steps == 0 || start == end)
		return (start);
	s = int_to_color(start);
	e = int_to_color(end);
	ret.r = interpolate_component(s.r, e.r, curr, steps);
	ret.g = interpolate_component(s.g, e.g, curr, steps);
	ret.b = interpolate_component(s.b, e.b, curr, steps);
	ret.a = interpolate_component(s.a, e.a, curr, steps);
	return (color_to_int(ret));
}

static t_color	int_to_color(uint32_t i)
{
	t_color	c;

	c.r = (i >> 24) & 0xff;
	c.g = (i >> 16) & 0xff;
	c.b = (i >> 8) & 0xff;
	c.a = i & 0xff;
	return (c);
}

static uint32_t	color_to_int(t_color c)
{
	uint32_t	i;

	i = (uint32_t)(c.r << 24 | c.g << 16 | c.b << 8 | c.a);
	return (i);
}

static uint8_t	interpolate_component(uint8_t s, uint8_t e, int cur, int steps)
{
	int	ret;

	if (steps == 0)
		return (s);
	ret = s + (int)round((double)cur / (double)steps * (e - s));
	return ((uint8_t)ret);
}
