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
void draw_horizontal_lines(t_render_context *ctx, t_map *map) {
    int i, j, k;
    t_point curr;

    for (i = 0; i < map->rows; i++) {
        j = 0;
        while (j < map->cols) {
            curr = map->points[i][j];

            // Draw lines for flat segments
            k = j + 1;
            while (k < map->cols && map->points[i][k].elevation == curr.elevation) {
                k++;
            }
            draw_line(ctx, curr, map->points[i][k - 1]);

            // Draw line to next point if it exists and is not part of the flat segment
            if (k < map->cols) {
                draw_line(ctx, map->points[i][k - 1], map->points[i][k]);
            }

            j = k;
        }
    }
}

void draw_vertical_lines(t_render_context *ctx, t_map *map) {
    int i, j, k;
    t_point curr;

    for (j = 0; j < map->cols; j++) {
        i = 0;
        while (i < map->rows) {
            curr = map->points[i][j];

            // Draw lines for flat segments
            k = i + 1;
            while (k < map->rows && map->points[k][j].elevation == curr.elevation) {
                k++;
            }
            draw_line(ctx, curr, map->points[k - 1][j]);

            // Draw line to next point if it exists and is not part of the flat segment
            if (k < map->rows) {
                draw_line(ctx, map->points[k - 1][j], map->points[k][j]);
            }

            i = k;
        }
    }
}

void draw(t_render_context *ctx, t_map *map) {
    draw_horizontal_lines(ctx, map);
    draw_vertical_lines(ctx, map);
}

void	bresenham(t_render_context *ctx, t_line line, t_gradient colors);
void	draw_line(t_render_context *ctx, t_point begin, t_point end)
{
	t_line		line;
	t_gradient	colors;

	colors.start = begin.color;
	colors.curr = colors.start;
	colors.end = end.color;
	line.x0 = begin.pixel_x;
	line.y0 = begin.pixel_y;
	line.x1 = end.pixel_x;
	line.y1 = end.pixel_y;
	if (clip(&line))
		bresenham(ctx, line, colors);
}
