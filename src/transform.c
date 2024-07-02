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

static t_vecd	rotate(t_vecd vec, t_vector rotation)
{
	(void)rotation;
	return (vec);
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
	u = ft_vecd_add(u, center);
	v = ft_vecd_add(v, center);
	u = rotate(u, T->rotation);
	v = rotate(v, T->rotation);
	u = ft_vecd_add(u, ft_vecd_mul(center, -1));
	v = ft_vecd_add(v, ft_vecd_mul(center, -1));
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
