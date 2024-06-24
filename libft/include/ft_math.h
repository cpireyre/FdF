#ifndef FT_MATH_H
# define FT_MATH_H

typedef struct s_vector
{
	int	x;
	int	y;
	int	z;
	int	c;
}		t_vector;

t_vector	to_vec2(int x, int y);

int	ft_abs(int a);
int	ft_min(int a, int b);
int	ft_max(int a, int b);
int	ft_sign(int a, int b);

#endif /* FT_MATH_H */
