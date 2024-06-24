#include "rasterize.h"

static t_clip_outcode	compute_outcode(int x, int y, int xmax, int ymax);
static t_vec2	clamp(t_line *l, int xmax, int ymax, t_clip_outcode code);
static t_vec2	to_vec(int x, int y);

/* https://en.wikipedia.org/wiki/Cohen–Sutherland_algorithm */

int clip(t_line *line, int xmax, int ymax)
{
	t_clip_outcode	code0;
	t_clip_outcode	code1;
	t_vec2		clamped;

	while (1)
	{
		code0 = compute_outcode(line->x0, line->y0, xmax, ymax);
		code1 = compute_outcode(line->x1, line->y1, xmax, ymax);
		if (!(code0 | code1))
			return (1);
		else if (code0 & code1)
			return (0);
		if (code0 > code1)
		{
			clamped = clamp(line, xmax, ymax, code0);
			line->x0 = clamped.x;
			line->y0 = clamped.y;
		}
		else
		{
			clamped = clamp(line, xmax, ymax, code1);
			line->x1 = clamped.x;
			line->y1 = clamped.y;
		}
	}
}

static t_clip_outcode	compute_outcode(int x, int y, int xmax, int ymax)
{
	t_clip_outcode	code;

	code = INSIDE;
	if (x < 0)
		code |= LEFT;
	else if (x >= xmax)
		code |= RIGHT;
	if (y < 0)
		code |= TOP;
	else if (y >= ymax)
		code |= BOTTOM;
	return (code);
}

static t_vec2	clamp(t_line *l, int xmax, int ymax, t_clip_outcode code)
{
	double	slope;
	t_vec2	clamped;

	slope = (double)(l->y1 - l->y0) / (double)(l->x1 - l->x0);
	clamped = to_vec(0, 0);
	if (code & TOP)
		clamped = to_vec(l->x0 - (int)round(l->y0 / slope), 0);
	else if (code & BOTTOM)
		clamped = to_vec(l->x0 + (int)round((ymax - l->y0) / slope), ymax - 1);
	else if (code & RIGHT)
		clamped = to_vec(xmax - 1, l->y0 + (int)round(slope * (xmax - l->x0)));
	else if (code & LEFT)
		clamped = to_vec(0, l->y0 - (int)round(slope * l->x0));
	return (clamped);
}

static t_vec2	to_vec(int x, int y)
{
	t_vec2	v;

	v.x = x;
	v.y = y;
	return (v);
}
