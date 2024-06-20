/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:15:50 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/20 14:12:48 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpolate_colors.h"
#include "libft.h"

static uint32_t	color_to_int(t_color c);
static t_color	int_to_color(uint32_t i);
static uint8_t	interpolate_component(uint8_t s, uint8_t e, int cur, int steps);

uint32_t	interpolate_color(uint32_t start, uint32_t end, int curr, int steps)
{
	t_color	s;
	t_color	e;
	t_color	ret;

	s = int_to_color(start);
	e = int_to_color(end);
	ret.r = interpolate_component(s.r, e.r, curr, steps);
	ret.g = interpolate_component(s.g, e.g, curr, steps);
	ret.b = interpolate_component(s.b, e.b, curr, steps);
	ret.a = interpolate_component(s.a, e.a, curr, steps);
	return (color_to_int(ret));
}

static t_color	int_to_color(uint32_t i)
{
	t_color	c;

	c.r = (i >> 24) & 0xff;
	c.g = (i >> 16) & 0xff;
	c.b = (i >> 8) & 0xff;
	c.a = i & 0xff;
	return (c);
}

static uint32_t	color_to_int(t_color c)
{
	uint32_t	i;

	i = (uint32_t)(c.r << 24 | c.g << 16 | c.b << 8 | c.a);
	return (i);
}

static uint8_t	interpolate_component(uint8_t s, uint8_t e, int cur, int steps)
{
	int	ret;
	int	fcur;
	int	fsteps;

	fcur = to_fixed_point(cur);
	fsteps = to_fixed_point(steps);
	ret = to_fixed_point(s) + fixed_point_divide(fcur * (e - s), fsteps);
	return ((uint8_t)to_integer(ret));
}
