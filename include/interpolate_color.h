/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate_color.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:49:59 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/26 14:53:21 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPOLATE_COLOR_H
# define INTERPOLATE_COLOR_H

# include <stdint.h>
# include <math.h>

extern uint32_t	interpolate_color(uint32_t start, uint32_t end, double lerp);

struct s_ch
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
};

typedef union u_color
{
	struct s_ch	ch;
	uint32_t	value;
}	t_color;

#endif /* INTERPOLATE_COLOR_H */
