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
	int			yaw;
	int			pitch;
	int			roll;
	int			scale;
	int			offset_x;
	int			offset_y;
	double		cos_yaw;
	double		sin_yaw;
	double		cos_pitch;
	double		sin_pitch;
	double		cos_roll;
	double		sin_roll;
}				t_transform;

extern t_v3d	calculate_center(t_line *lines, int num_lines);
extern t_line	transform(t_line line, t_transform *T, t_v3d center);

#endif /* TRANSFORM_H */
