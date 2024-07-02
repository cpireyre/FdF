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

t_vecd	ft_vecd_add(t_vecd a, t_vecd b)
{
	return ((t_vecd){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vecd	ft_vecd_mul(t_vecd a, int n)
{
	return ((t_vecd){n * a.x, n * a.y, n * a.z});
}
