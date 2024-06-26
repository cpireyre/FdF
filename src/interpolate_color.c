/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:28:57 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/26 13:28:58 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpolate_color.h"

uint32_t	interpolate_color(uint32_t start, uint32_t end, double lerp)
{
	t_color	s;
	t_color	e;
	t_color	ret;

	if (start == end)
		return (start);
	s.value = start;
	e.value = end;
	ret.ch.r = (uint8_t)fmax(0, fmin(255, fma(lerp, e.ch.r - s.ch.r, s.ch.r)));
	ret.ch.g = (uint8_t)fmax(0, fmin(255, fma(lerp, e.ch.g - s.ch.g, s.ch.g)));
	ret.ch.b = (uint8_t)fmax(0, fmin(255, fma(lerp, e.ch.b - s.ch.b, s.ch.b)));
	ret.ch.a = (uint8_t)fmax(0, fmin(255, fma(lerp, e.ch.a - s.ch.a, s.ch.a)));
	return (ret.value);
}
