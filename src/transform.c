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

static t_v2i	project(t_v3d v, t_transform *T);

t_v3d	calculate_center(t_line *lines, int num_lines)
{
	t_v3d	sum;
	int		count;
	int		i;

	i = 0;
	count = 0;
	sum = v3dd(0);
	while (i < num_lines)
	{
		sum = v3d_add(sum, v3d_add(lines[i].world0, lines[i].world1));
		count += 2;
		i++;
	}
	return (v3d_div(sum, v3dd(count)));
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

static t_v2i	project(t_v3d v, t_transform *T)
{
	t_v3d	iso;
	t_v3d	scaled_iso;
	t_v2i	result;

	iso.x = (v.x - v.y) * COS45;
	iso.y = (v.x + v.y) * SIN45 - v.z;
	scaled_iso.x = (double)T->scale / (double)10 * iso.x;
	scaled_iso.y = (double)T->scale / (double)10 * iso.y;
	result.x = (int)(T->offset_x + scaled_iso.x);
	result.y = (int)(T->offset_y + scaled_iso.y);
	return (result);
}

t_line	transform(t_line line, t_transform *T, t_v3d center)
{
	t_v3d	u;
	t_v3d	v;

	u = line.world0;
	v = line.world1;
	u = v3d_add(u, v3d_mul(center, v3dd(-1)));
	v = v3d_add(v, v3d_mul(center, v3dd(-1)));
	u = rotate_yaw(u, T->cos_yaw, T->sin_yaw);
	v = rotate_yaw(v, T->cos_yaw, T->sin_yaw);
	u = rotate_pitch(u, T->cos_pitch, T->sin_pitch);
	v = rotate_pitch(v, T->cos_pitch, T->sin_pitch);
	u = rotate_roll(u, T->cos_roll, T->sin_roll);
	v = rotate_roll(v, T->cos_roll, T->sin_roll);
	u = v3d_add(u, center);
	v = v3d_add(v, center);
	line.world0 = u;
	line.world1 = v;
	line.screen0 = project(u, T);
	line.screen1 = project(v, T);
	return (line);
}
