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

static t_vecd	project(t_vecd v, t_transform *T);

t_vecd	calculate_center(t_line *lines, int num_lines)
{
	t_vecd	sum;
	int		count;
	int		i;

	i = 0;
	count = 0;
	ft_bzero(&sum, sizeof(sum));
	while (i < num_lines)
	{
		sum.x += lines[i].x0 + lines[i].x1;
		sum.y += lines[i].y0 + lines[i].y1;
		sum.z += lines[i].z0 + lines[i].z1;
		count += 2;
		i++;
	}
	return ((t_vecd){sum.x / count, sum.y / count, sum.z / count});
}

static t_vecd	rotate_yaw(t_vecd u, double cos_yaw, double sin_yaw)
{
	t_vecd	ret;

	ret = u;
	ret.x = u.x * cos_yaw - u.y * sin_yaw;
	ret.y = u.x * sin_yaw + u.y * cos_yaw;
	ret.z = u.z;
	return (ret);
}

static t_vecd	rotate_pitch(t_vecd u, double cos_pitch, double sin_pitch)
{
	t_vecd	ret;

	ret = u;
	ret.x = u.x * cos_pitch + u.z * sin_pitch;
	ret.y = u.y;
	ret.z = -u.x * sin_pitch + u.z * cos_pitch;
	return (ret);
}

static t_vecd	rotate_roll(t_vecd u, double cos_roll, double sin_roll)
{
	t_vecd	ret;

	ret = u;
	ret.x = u.x;
	ret.y = u.y * cos_roll - u.z * sin_roll;
	ret.z = u.y * sin_roll + u.z * cos_roll;
	return (ret);
}

static t_vecd	project(t_vecd v, t_transform *T)
{
	t_vecd	iso;
	t_vecd	scaled_iso;

	iso.x = (v.x - v.y) * COS45;
	iso.y = (v.x + v.y) * SIN45 - v.z;
	scaled_iso.x = (double)T->scale / (double)10 * iso.x;
	scaled_iso.y = (double)T->scale / (double)10 * iso.y;
	v.x = T->offset_x + scaled_iso.x;
	v.y = T->offset_y + scaled_iso.y;
	return (v);
}

t_line	transform(t_line line, t_transform *T, t_vecd center)
{
	t_vecd	u;
	t_vecd	v;

	u = ft_vecd_from_int(line.x0, line.y0, line.z0);
	v = ft_vecd_from_int(line.x1, line.y1, line.z1);
	u = ft_vecd_add(u, ft_vecd_mul(center, -1));
	v = ft_vecd_add(v, ft_vecd_mul(center, -1));
	u = rotate_yaw(u, T->cos_yaw, T->sin_yaw);
	v = rotate_yaw(v, T->cos_yaw, T->sin_yaw);
	u = rotate_pitch(u, T->cos_pitch, T->sin_pitch);
	v = rotate_pitch(v, T->cos_pitch, T->sin_pitch);
	u = rotate_roll(u, T->cos_roll, T->sin_roll);
	v = rotate_roll(v, T->cos_roll, T->sin_roll);
	u = ft_vecd_add(u, center);
	v = ft_vecd_add(v, center);
	u = project(u, T);
	v = project(v, T);
	line.x0 = (int)round(u.x);
	line.y0 = (int)round(u.y);
	line.z0 = (int)round(u.z);
	line.x1 = (int)round(v.x);
	line.y1 = (int)round(v.y);
	line.z1 = (int)round(v.z);
	return (line);
}
