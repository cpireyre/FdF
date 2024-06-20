/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate_colors.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:23:51 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/20 13:49:53 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPOLATE_COLORS_H
# define INTERPOLATE_COLORS_H

# include <stdint.h>

# define R_MASK 0xff000000
# define G_MASK 0x00ff0000
# define B_MASK 0x0000ff00
# define A_MASK 0x000000ff

uint32_t	interpolate_color(uint32_t start, uint32_t end, int cur, int steps);

typedef struct	s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}
				t_color;

#endif /* INTERPOLATE_COLORS_H */
