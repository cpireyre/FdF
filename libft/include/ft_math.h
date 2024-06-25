#ifndef FT_MATH_H
# define FT_MATH_H

typedef struct s_vector
{
	int	x;
	int	y;
	int	z;
	int	c;
}		t_vector;

t_vector	ft_vec2(int x, int y);
double		ft_distance(int x0, int y0, int x1, int y1);

int	ft_abs(int a);
int	ft_min(int a, int b);
int	ft_max(int a, int b);
int	ft_sign(int a, int b);

#endif /* FT_MATH_H */
