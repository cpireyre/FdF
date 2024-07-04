/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:08:46 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/02 13:13:22 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

t_v3d	ft_v3d_add(t_v3d a, t_v3d b)
{
	return ((t_v3d){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_v3d	ft_v3d_mul(t_v3d a, int n)
{
	return ((t_v3d){n * a.x, n * a.y, n * a.z});
}
