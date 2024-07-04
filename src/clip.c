/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:26:41 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/28 15:09:37 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clip.h"

static int				clip_line(t_line *line, int xmax, int ymax);
static t_clip_code		compute_code(int x, int y, int xmax, int ymax);
static t_v2i			clamp(t_line *l, int xmax, int ymax, t_clip_code code);

int	clip(t_line *line, int xmax, int ymax)
{
	t_line	orig;
	double	ratio0;
	double	ratio1;
	double	orig_len;

	orig = *line;
	if (clip_line(line, xmax, ymax))
	{
		orig_len = ft_distance(orig.screen0.x, orig.screen0.y, orig.screen1.x, orig.screen1.y);
		ratio0 = ft_distance(orig.screen0.x, orig.screen0.y, line->screen0.x, line->screen0.y) / orig_len;
		ratio1 = ft_distance(orig.screen0.x, orig.screen0.y, line->screen1.x, line->screen1.y) / orig_len;
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
	t_v2i	clamped;

	while (1)
	{
		code0 = compute_code(line->screen0.x, line->screen0.y, xmax, ymax);
		code1 = compute_code(line->screen1.x, line->screen1.y, xmax, ymax);
		if (!(code0 | code1))
			return (1);
		else if (code0 & code1)
			return (0);
		if (code0 > code1)
		{
			clamped = clamp(line, xmax, ymax, code0);
			line->screen0.x = clamped.x;
			line->screen0.y = clamped.y;
		}
		else
		{
			clamped = clamp(line, xmax, ymax, code1);
			line->screen1.x = clamped.x;
			line->screen1.y = clamped.y;
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

static t_v2i	clamp(t_line *l, int xmax, int ymax, t_clip_code code)
{
	t_v2i	ret;
	double		slope;

	ret = v2i(0, 0);
	slope = (double)(l->screen1.y - l->screen0.y) / (double)(l->screen1.x - l->screen0.x);
	if (code & TOP)
		ret = v2i(l->screen0.x - (int)round(l->screen0.y / slope), 0);
	else if (code & BOTTOM)
		ret = v2i(l->screen0.x + (int)round((ymax - l->screen0.y) / slope), ymax - 1);
	else if (code & RIGHT)
		ret = v2i(xmax - 1, l->screen0.y + (int)fma(slope, xmax - l->screen0.x, 0));
	else if (code & LEFT)
		ret = v2i(0, l->screen0.y - (int)fma(slope, l->screen0.x, 0));
	return (ret);
}
