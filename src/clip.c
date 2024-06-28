/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:26:41 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/28 15:07:13 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clip.h"

static int				clip_line(t_line *line, int xmax, int ymax);
static t_clip_code		compute_code(int x, int y, int xmax, int ymax);
static t_vector			clamp(t_line *l, int xmax, int ymax, t_clip_code code);

int	clip(t_line *line, int xmax, int ymax)
{
	t_line	orig;
	double	ratio0;
	double	ratio1;
	double	orig_len;

	orig = *line;
	if (clip_line(line, xmax, ymax))
	{
		orig_len = ft_distance(orig.x0, orig.y0, orig.x1, orig.y1);
		ratio0 = ft_distance(orig.x0, orig.y0, line->x0, line->y0) / orig_len;
		ratio1 = ft_distance(orig.x1, orig.y0, line->x0, line->y1) / orig_len;
		line->color0 = interpolate_color(
				(uint32_t)orig.color0, (uint32_t)orig.color1, ratio0);
		line->color1 = interpolate_color(
				(uint32_t)orig.color0, (uint32_t)orig.color1, ratio1);
		return (1);
	}
	return (0);
}

/* https://en.wikipedia.org/wiki/Cohen–Sutherland_algorithm */

static int	clip_line(t_line *line, int xmax, int ymax)
{
	t_clip_code	code0;
	t_clip_code	code1;
	t_vector	clamped;

	while (1)
	{
		code0 = compute_code(line->x0, line->y0, xmax, ymax);
		code1 = compute_code(line->x1, line->y1, xmax, ymax);
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

static t_clip_code	compute_code(int x, int y, int xmax, int ymax)
{
	t_clip_code	code;

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

static t_vector	clamp(t_line *l, int xmax, int ymax, t_clip_code code)
{
	t_vector	ret;
	double		slope;

	ret = ft_vec2(0, 0);
	slope = (double)(l->y1 - l->y0) / (double)(l->x1 - l->x0);
	if (code & TOP)
		ret = ft_vec2(l->x0 - (int)round(l->y0 / slope), 0);
	else if (code & BOTTOM)
		ret = ft_vec2(l->x0 + (int)round((ymax - l->y0) / slope), ymax - 1);
	else if (code & RIGHT)
		ret = ft_vec2(xmax - 1, l->y0 + (int)fma(slope, xmax - l->x0, 0));
	else if (code & LEFT)
		ret = ft_vec2(0, l->y0 - (int)fma(slope, l->x0, 0));
	return (ret);
}
