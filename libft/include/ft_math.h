#ifndef FT_MATH_H
# define FT_MATH_H

# include "fixed_point.h"

int	ft_abs(int a);
int	ft_min(int a, int b);
int	ft_max(int a, int b);
int	ft_sign(int a, int b);


typedef struct s_vec2
{
	int	x;
	int	y;
}				t_vec2;

#endif /* FT_MATH_H */
