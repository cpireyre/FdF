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

#include "draw.h"
#include "config.h"
#include "t_tuple.h"
#include <math.h>
#include "libft.h"

static t_outcode	compute_outcode(double x, double y);

/* Cohen–Sutherland, wip */
int clip(t_line *line)
{
	// compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
	t_outcode outcode0 = compute_outcode(line->x0, line->y0);
	t_outcode outcode1 = compute_outcode(line->x1, line->y1);
	int accept = 0;
	double x0, y0, x1, y1;

	x0 = (double)line->x0;
	x1 = (double)line->x1;
	y0 = (double)line->y0;
	y1 = (double)line->y1;
	while (1) {
		if (!(outcode0 | outcode1)) {
			// bitwise OR is 0: both points inside window; trivially accept and exit loop
			accept = 1;
			break;
		} else if (outcode0 & outcode1) {
			// bitwise AND is not 0: both points share an outside zone (LEFT, RIGHT, TOP,
			// or BOTTOM), so both must be outside window; exit loop (accept is false)
			break;
		} else {
			// failed both tests, so calculate the line segment to clip
			// from an outside point to an intersection with clip edge
			double x, y;

			// At least one endpoint is outside the clip rectangle; pick it.
			t_outcode outcodeOut = outcode1 > outcode0 ? outcode1 : outcode0;

			// Now find the intersection point;
			// use formulas:
			//   slope = (y1 - y0) / (x1 - x0)
			//   x = x0 + (1 / slope) * (ym - y0), where ym is ymin or ymax
			//   y = y0 + slope * (xm - x0), where xm is xmin or xmax
			// No need to worry about divide-by-zero because, in each case, the
			// outcode bit being tested guarantees the denominator is non-zero
			if (outcodeOut & TOP) {           // point is above the clip window
				x = x0 + (x1 - x0) * (0 - y0) / (y1 - y0);
				y = 0;
			} else if (outcodeOut & BOTTOM) { // point is below the clip window
				x = x0 + (x1 - x0) * (WIN_HEIGHT - y0) / (y1 - y0);
				y = WIN_HEIGHT - 1;
			} else if (outcodeOut & RIGHT) {  // point is to the right of clip window
				y = y0 + (y1 - y0) * (WIN_WIDTH - x0) / (x1 - x0);
				x = WIN_WIDTH - 1;
			} else if (outcodeOut & LEFT) {   // point is to the left of clip window
				y = y0 + (y1 - y0) * (0 - x0) / (x1 - x0);
				x = 0;
			}

			// Now we move outside point to intersection point to clip
			// and get ready for next pass.
			if (outcodeOut == outcode0) {
				x0 = x;
				y0 = y;
				outcode0 = compute_outcode(x0, y0);
			} else {
				x1 = x;
				y1 = y;
				outcode1 = compute_outcode(x1, y1);
			}
		}
	}
	line->x0 = (int)round(x0);
	line->x1 = (int)round(x1);
	line->y0 = (int)round(y0);
	line->y1 = (int)round(y1);
	return accept;
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
