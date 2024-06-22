/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:10:25 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/21 12:13:07 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "t_map.h"
#include "config.h"
#include "draw.h"
#include "render.h"

void	draw_line(t_render_context *ctx, t_point begin, t_point end);
void	draw(t_render_context *ctx, t_map *map)
{
	int		i;
	int		j;
	t_point	curr;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			curr = map->points[i][j];
			if (i + 1 < map->rows)
				draw_line(ctx, curr, map->points[i + 1][j]);
			if (j + 1 < map->cols)
				draw_line(ctx, curr, map->points[i][j + 1]);
			j++;
		}
		i++;
	}
}

void	bresenham(t_render_context *ctx, t_line line, t_gradient colors);
void	draw_line(t_render_context *ctx, t_point begin, t_point end)
{
	t_line		line;
	t_gradient	colors;

	line.x0 = begin.pixel_x;
	line.y0 = begin.pixel_y;
	line.x1 = end.pixel_x;
	line.y1 = end.pixel_y;
	colors.start = begin.color;
	colors.end = end.color;
	if (clip(&line))
		bresenham(ctx, line, colors);
}
