/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:36:12 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/20 13:44:03 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fixed_point.h"

int	to_fixed_point(int n)
{
	return (n << FP_SHIFT);
}

int	to_integer(int n)
{
	return ((n + FP_HALF) >> FP_SHIFT);
}

int	fixed_point_multiply(int a, int b)
{
	return ((a * b) >> FP_SHIFT);
}

int	fixed_point_divide(int a, int b)
{
	return ((a << FP_SHIFT) / b);
}
