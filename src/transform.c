/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:21:31 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/28 12:50:21 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transform.h"

static t_vector	project_vec(t_vector v, t_projection *s);

t_line	project_line(t_line line, t_projection *s)
{
	t_vector	u;
	t_vector	v;
	t_line		projection;

	projection = line;
	u = ft_vec3(line.x0, line.y0, line.z0);
	v = ft_vec3(line.x1, line.y1, line.z1);
	u = project_vec(u, s);
	v = project_vec(v, s);
	projection.x0 = u.x;
	projection.y0 = u.y;
	projection.z0 = u.z;
	projection.x1 = v.x;
	projection.y1 = v.y;
	projection.z1 = v.z;
	return (projection);
}

static t_vector	project_vec(t_vector v, t_projection *s)
{
	double	iso_x;
	double	iso_y;
	double	scaled_iso_x;
	double	scaled_iso_y;

	iso_x = (v.x - v.y) * cos(s->angle);
	iso_y = (v.x + v.y) * sin(s->angle) - v.z;
	scaled_iso_x = s->scale * iso_x;
	scaled_iso_y = s->scale * iso_y;
	v.x = s->offset_x + (int)round(scaled_iso_x);
	v.y = s->offset_y + (int)round(scaled_iso_y);
	return (v);
}
