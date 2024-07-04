/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_vec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:34:15 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/28 11:19:30 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_la.h"

t_v4i	ft_vec2(int x, int y)
{
	t_v4i	v;

	v.x = x;
	v.y = y;
	return (v);
}

t_v4i	ft_vec3(int x, int y, int z)
{
	t_v4i	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}
