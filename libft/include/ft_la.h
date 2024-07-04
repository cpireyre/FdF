/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_la.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:15:15 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/04 12:26:36 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LA_H
# define FT_LA_H

/* 2 dimensions */

typedef struct s_v2i
{
	int	x;
	int	y;
}		t_v2i;

typedef struct s_v2d
{
	double	x;
	double	y;
}				t_v2d;

typedef struct s_v2u
{
	unsigned int	x;
	unsigned int	y;
}				t_v2u;

/* 3 dimensions */

typedef struct s_v3i
{
	int	x;
	int	y;
	int	z;
}		t_v3i;

typedef struct s_v3d
{
	double	x;
	double	y;
	double	z;
}				t_v3d;

typedef struct s_v3u
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	z;
}				t_v3u;

/* 4 dimensions */

typedef struct s_v4i
{
	int	x;
	int	y;
	int	z;
	int	w;
}		t_v4i;

typedef struct s_v4d
{
	double	x;
	double	y;
	double	z;
	double	w;
}				t_v4d;

typedef struct s_v4u
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	z;
	unsigned int	w;
}				t_v4u;

t_v2i	v2i(int x, int y);
t_v3i	v3i(int x, int y, int z);
t_v3d	v3d_add(t_v3d a, t_v3d b);
t_v3d	v3d_mul(t_v3d a, int n);
t_v3d	v3d(int x, int y, int z);

double		ft_distance(int x0, int y0, int x1, int y1);

int			ft_abs(int a);
int			ft_min(int a, int b);
int			ft_max(int a, int b);
int			ft_sign(int a, int b);

#endif /* FT_LA_H */
