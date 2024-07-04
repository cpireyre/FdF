/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v3d_from_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:23:35 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/02 13:24:02 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

t_v3d	ft_v3d_from_int(int x, int y, int z)
{
	return ((t_v3d){(double)x, (double)y, (double)z});
}
