/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_point.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:37:24 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/20 13:40:06 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_POINT_H
# define FIXED_POINT_H

# define FP_SHIFT 16
# define FP_ONE (1 << FP_SHIFT)
# define FP_HALF (FP_ONE >> 1)

extern int	to_fixed_point(int n);
extern int	to_integer(int n);
extern int	fixed_point_multiply(int a, int b);
extern int	fixed_point_divide(int a, int b);

#endif /* FIXED_POINT_H */
