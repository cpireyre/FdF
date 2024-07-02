/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:07:22 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/02 11:22:55 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
# define TRANSFORM_H

# include "t_line.h"
# include "libft.h"
# include <math.h>

typedef struct s_vecd
{
	double	x;
	double	y;
	double	z;
}				t_vecd;

typedef struct s_transform
{
	t_vector	rotation;
	int			scale;
	int			offset_x;
	int			offset_y;
}				t_transform;

extern t_vecd	calculate_center(t_line *lines, int num_lines);
extern t_line	transform(t_line line, t_transform *T, t_vecd center);

#endif /* TRANSFORM_H */
