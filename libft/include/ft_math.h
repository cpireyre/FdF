/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:31:05 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/02 13:25:07 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

typedef struct s_vector
{
	int	x;
	int	y;
	int	z;
	int	c;
}		t_vector;

typedef struct s_vecd
{
	double	x;
	double	y;
	double	z;
}				t_vecd;

t_vector	ft_vec2(int x, int y);
t_vector	ft_vec3(int x, int y, int z);
t_vecd		ft_vecd_add(t_vecd a, t_vecd b);
t_vecd		ft_vecd_mul(t_vecd a, int n);
t_vecd		ft_vecd_from_int(int x, int y, int z);

double		ft_distance(int x0, int y0, int x1, int y1);

int			ft_abs(int a);
int			ft_min(int a, int b);
int			ft_max(int a, int b);
int			ft_sign(int a, int b);

#endif /* FT_MATH_H */
