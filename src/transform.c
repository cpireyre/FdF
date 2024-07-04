/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:32:00 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/02 13:25:55 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transform.h"

static t_v3d	project(t_v3d v, t_transform *T);

t_v3d	calculate_center(t_line *lines, int num_lines)
{
	t_v3d	sum;
	int		count;
	int		i;

	i = 0;
	count = 0;
	ft_bzero(&sum, sizeof(sum));
	while (i < num_lines)
	{
		sum.x += lines[i].world0.x + lines[i].world1.x;
		sum.y += lines[i].world0.y + lines[i].world1.y;
		sum.z += lines[i].world0.z + lines[i].world1.z;
		count += 2;
		i++;
	}
	return ((t_v3d){sum.x / count, sum.y / count, sum.z / count});
}

static t_v3d	rotate_yaw(t_v3d u, double cos_yaw, double sin_yaw)
{
	t_v3d	ret;

	ret = u;
	ret.x = u.x * cos_yaw - u.y * sin_yaw;
	ret.y = u.x * sin_yaw + u.y * cos_yaw;
	ret.z = u.z;
	return (ret);
}

static t_v3d	rotate_pitch(t_v3d u, double cos_pitch, double sin_pitch)
{
	t_v3d	ret;

	ret = u;
	ret.x = u.x * cos_pitch + u.z * sin_pitch;
	ret.y = u.y;
	ret.z = -u.x * sin_pitch + u.z * cos_pitch;
	return (ret);
}

static t_v3d	rotate_roll(t_v3d u, double cos_roll, double sin_roll)
{
	t_v3d	ret;

	ret = u;
	ret.x = u.x;
	ret.y = u.y * cos_roll - u.z * sin_roll;
	ret.z = u.y * sin_roll + u.z * cos_roll;
	return (ret);
}

static t_v3d	project(t_v3d v, t_transform *T)
{
	t_v3d	iso;
	t_v3d	scaled_iso;

	iso.x = (v.x - v.y) * COS45;
	iso.y = (v.x + v.y) * SIN45 - v.z;
	scaled_iso.x = (double)T->scale / (double)10 * iso.x;
	scaled_iso.y = (double)T->scale / (double)10 * iso.y;
	v.x = T->offset_x + scaled_iso.x;
	v.y = T->offset_y + scaled_iso.y;
	return (v);
}

t_line	transform(t_line line, t_transform *T, t_v3d center)
{
	t_v3d	u;
	t_v3d	v;

	u = line.world0;
	v = line.world1;
	u = ft_v3d_add(u, ft_v3d_mul(center, -1));
	v = ft_v3d_add(v, ft_v3d_mul(center, -1));
	u = rotate_yaw(u, T->cos_yaw, T->sin_yaw);
	v = rotate_yaw(v, T->cos_yaw, T->sin_yaw);
	u = rotate_pitch(u, T->cos_pitch, T->sin_pitch);
	v = rotate_pitch(v, T->cos_pitch, T->sin_pitch);
	u = rotate_roll(u, T->cos_roll, T->sin_roll);
	v = rotate_roll(v, T->cos_roll, T->sin_roll);
	u = ft_v3d_add(u, center);
	v = ft_v3d_add(v, center);
	u = project(u, T);
	v = project(v, T);
	line.world0 = u;
	line.world1 = v;
	line.screen0.x = (int)round(u.x);
	line.screen0.y = (int)round(u.y);
	line.screen0.z = (int)round(u.z);
	line.screen1.x = (int)round(v.x);
	line.screen1.y = (int)round(v.y);
	line.screen1.z = (int)round(v.z);
	return (line);
}
