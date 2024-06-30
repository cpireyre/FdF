void	ft_swap(int *x, int *y)
{
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;
}
