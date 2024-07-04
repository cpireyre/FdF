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

typedef struct s_v4i
{
	int	x;
	int	y;
	int	z;
	int	c;
}		t_v4i;

typedef struct s_v3d
{
	double	x;
	double	y;
	double	z;
}				t_v3d;

typedef struct s_v2i
{
	int	x;
	int	y;
}				t_v2i;

typedef struct s_v3u
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	z;
}				t_v3u;

t_v4i	ft_vec2(int x, int y);
t_v4i	ft_vec3(int x, int y, int z);
t_v3d		ft_v3d_add(t_v3d a, t_v3d b);
t_v3d		ft_v3d_mul(t_v3d a, int n);
t_v3d		ft_v3d_from_int(int x, int y, int z);

double		ft_distance(int x0, int y0, int x1, int y1);

int			ft_abs(int a);
int			ft_min(int a, int b);
int			ft_max(int a, int b);
int			ft_sign(int a, int b);

t_v2i v2i3d(t_v3d a);
t_v3d	v3d_add(t_v3d a, t_v3d b);
t_v3d	v3dd(double x);
t_v3d	v3d_div(t_v3d a, t_v3d b);
t_v3d	v3d_mul(t_v3d a, t_v3d b);

#endif /* FT_MATH_H */
