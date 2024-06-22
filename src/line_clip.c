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

#include "config.h"
#include "draw.h"

static t_outcode	compute_outcode(int x, int y);

/* Cohen–Sutherland, wip */
int	clip(t_line *line)
{
	t_outcode	outcode0;
	t_outcode	outcode1;

	outcode0 = compute_outcode(line->x0, line->y0);
	outcode1 = compute_outcode(line->x1, line->y1);
	if (outcode0 & outcode1)
		return (0);
	return (1);
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

