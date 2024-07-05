/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:07:22 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/05 11:00:37 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
# define TRANSFORM_H

# include "libft.h"
# include "t_line.h"
# include <math.h>

# define COS45 0.707107
# define SIN45 0.707107

/* rotation.x is yaw */
/* rotation.y is pitch */
/* rotation.z is roll */

typedef struct s_transform
{
	t_v3i		rotation;
	t_v2i		offset;
	double		cos_yaw;
	double		sin_yaw;
	double		cos_pitch;
	double		sin_pitch;
	double		cos_roll;
	double		sin_roll;
	int			scale;
}				t_transform;

t_line	transform(t_transform *T, t_v3d center, t_line line);

#endif /* TRANSFORM_H */
