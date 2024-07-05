/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_line.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:32:59 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/05 10:55:02 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_LINE_H
# define T_LINE_H

# include "libft.h"

typedef struct s_line
{
	t_v2i		screen0;
	t_v2i		screen1;
	t_v3d		world0;
	t_v3d		world1;
	int			length;
	t_v2i		delta;
	int			z_dir;
	t_v2i		slope;
	uint32_t	color0;
	uint32_t	color1;
	double		step;
}				t_line;

#endif /* T_LINE_H */
