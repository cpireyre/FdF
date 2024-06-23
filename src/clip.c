/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:54:36 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/21 12:14:28 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clip.h"

static t_outcode	compute_outcode(double x, double y);
static int	clip_recur(struct s_line_d *l);
static void	clamp(struct s_line_d *l, double *x0, double *y0, t_outcode code);

struct s_line_d	lift_to_double(t_line line)
{
	struct s_line_d	l;

	l.x0 = (double)line.x0;
	l.y0 = (double)line.y0;
	l.x1 = (double)line.x1;
	l.y1 = (double)line.y1;
	return (l);
}

t_line	lower_to_int(struct s_line_d l)
{
	t_line	line;

	line.x0 = (int)l.x0;
	line.y0 = (int)l.y0;
	line.x1 = (int)l.x1;
	line.y1 = (int)l.y1;
	return (line);
}

/* Recursive Cohen–Sutherland */
int clip(t_line *line)
{
	int				ret;
	struct s_line_d	l;

	l = lift_to_double(*line);
	ret = clip_recur(&l);
	*line = lower_to_int(l);
	return (ret);
}

static int	clip_recur(struct s_line_d *l)
{
	t_outcode code0;
	t_outcode code1;

	code0 = compute_outcode(l->x0, l->y0);
	code1 = compute_outcode(l->x1, l->y1);
	if (!(code0 | code1))
		return (1);
	if (code0 & code1)
		return (0);
	if (code0 > code1)
		clamp(l, &l->x0, &l->y0, code0);
	else
		clamp(l, &l->x1, &l->y1, code1);
	return (clip_recur(l));
}

static void	clamp(struct s_line_d *l, double *x0, double *y0, t_outcode code)
{
	double	x;
	double	y;
	double	slope;

	x = -1;
	y = -1;
	slope = (l->y1 - l->y0) / (l->x1 - l->x0);
	if (code & TOP)
	{
		x = l->x0 - (l->y0 / slope);
		y = 0;
	}
	else if (code & BOTTOM)
	{
		x = l->x0 + (WIN_HEIGHT - l->y0) / slope;
		y = WIN_HEIGHT - 1;
	}
	else if (code & RIGHT)
	{
		y = l->y0 + slope * (WIN_WIDTH - l->x0);
		x = WIN_WIDTH - 1;
	}
	else if (code & LEFT)
	{
		y = l->y0 - slope * l->x0;
		x = 0;
	}
	*x0 = x;
	*y0 = y;
}

static t_outcode	compute_outcode(double x, double y)
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
