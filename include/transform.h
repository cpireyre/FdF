/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:07:22 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/02 13:10:21 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
# define TRANSFORM_H

# include "libft.h"
# include "t_line.h"
# include <math.h>

# define COS45 0.707107
# define SIN45 0.707107

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
