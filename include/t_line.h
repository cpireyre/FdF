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

# include "libft.h"

typedef struct s_line
{
	t_v4i	screen0;
	t_v4i	screen1;
	t_v3d		world0;
	t_v3d		world1;
	int			length;
	int			delta_x;
	int			delta_y;
	int			z_dir;
	int			slope_x;
	int			slope_y;
	uint32_t	color0;
	uint32_t	color1;
	int			should_render;
}				t_line;

#endif /* T_LINE_H */
