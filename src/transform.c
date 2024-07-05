/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:32:00 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/05 11:00:30 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transform.h"

static t_v2i	project(t_transform *T, t_v3d v);
static t_v3d	rotate(t_transform *T, t_v3d a);

t_line	transform(t_transform *T, t_v3d center, t_line line)
{
	{
		line.world0 = v3d_add(line.world0, v3d_mul(center, v3dd(-1)));
		line.world0 = rotate(T, line.world0);
		line.world0 = v3d_add(line.world0, center);
		line.screen0 = project(T, line.world0);
	}
	{
		line.world1 = v3d_add(line.world1, v3d_mul(center, v3dd(-1)));
		line.world1 = rotate(T, line.world1);
		line.world1 = v3d_add(line.world1, center);
		line.screen1 = project(T, line.world1);
	}
	return (line);
}

static t_v3d	rotate(t_transform *T, t_v3d a)
{
	t_v3d	yaw;
	t_v3d	pitch;
	t_v3d	roll;

	yaw.x = a.x * T->cos_yaw - a.y * T->sin_yaw;
	yaw.y = a.x * T->sin_yaw + a.y * T->cos_yaw;
	yaw.z = a.z;
	pitch.x = yaw.x * T->cos_pitch + yaw.z * T->sin_pitch;
	pitch.y = yaw.y;
	pitch.z = -yaw.x * T->sin_pitch + yaw.z * T->cos_pitch;
	roll.x = pitch.x;
	roll.y = pitch.y * T->cos_roll - pitch.z * T->sin_roll;
	roll.z = pitch.y * T->sin_roll + pitch.z * T->cos_roll;
	return (roll);
}

static t_v2i	project(t_transform *T, t_v3d v)
{
	t_v3d	iso;
	t_v3d	scaled_iso;
	t_v2i	result;

	iso.x = (v.x - v.y) * COS45;
	iso.y = (v.x + v.y) * SIN45 - v.z;
	scaled_iso.x = (double)T->scale / 10 * iso.x;
	scaled_iso.y = (double)T->scale / 10 * iso.y;
	result.x = (int)(T->offset.x + scaled_iso.x);
	result.y = (int)(T->offset.y + scaled_iso.y);
	return (result);
}
