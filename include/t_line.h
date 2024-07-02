/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_line.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:32:59 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/02 10:56:07 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_LINE_H
# define T_LINE_H

# include <stdint.h>

typedef struct s_line
{
	int			x0;
	int			y0;
	int			z0;
	int			x1;
	int			y1;
	int			z1;
	int			length;
	int			delta_x;
	int			delta_y;
	int			slope_x;
	int			slope_y;
	uint32_t	color0;
	uint32_t	color1;
	int			should_render;
}				t_line;

#endif /* T_LINE_H */
