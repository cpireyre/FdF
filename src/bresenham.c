/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:09:12 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/21 12:36:26 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "t_map.h"
#include "config.h"
#include "t_tuple.h"
#include "draw.h"
#include "render.h"
#include "interpolate_color.h"

void	bresenham(t_render_context *ctx, t_line line, t_gradient colors)
{
	int		i;
	int		err;
	int		steps;
	t_tuple	delta;
	t_tuple	slope;

	delta.x = ft_abs(line.x1 - line.x0);
	delta.y = -ft_abs(line.y1 - line.y0);
	slope.x = ft_sign(line.x0, line.x1);
	slope.y = ft_sign(line.y0, line.y1);
	steps = ft_max(delta.x, -delta.y);
	err = delta.x + delta.y;
	i = 0;
	while (line.x0 != line.x1 || line.y0 != line.y1)
	{
		ctx->plot(ctx->img, line.x0, line.y0, interpolate_color(colors.start, colors.end, i, steps));
		i++;
		int	double_err;

		double_err = err * 2;
		if (double_err > delta.y)
		{
			line.x0 += slope.x;
			err += delta.y;
		}
		if (double_err < delta.x)
		{
			line.y0 += slope.y;
			err += delta.x;
		}
	}
	ctx->plot(ctx->img, line.x1, line.y1, colors.end);
}
