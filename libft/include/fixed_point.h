/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_point.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:37:24 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/20 14:06:02 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_POINT_H
# define FIXED_POINT_H

# define FP_SHIFT	16
/* hardcoding because define can't refer to previous define due to norm */
# define FP_ONE		65536
# define FP_HALF 	32768

extern int	to_fixed_point(int n);
extern int	to_integer(int n);
extern int	fixed_point_multiply(int a, int b);
extern int	fixed_point_divide(int a, int b);

#endif /* FIXED_POINT_H */
