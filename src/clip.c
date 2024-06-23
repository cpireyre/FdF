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
