#include "fdf.h"

static void	print_matrix(t_matrix *m);

int	main(int argc, char **argv)
{
	int		i;
	t_matrix	m;

	i = 1;
	while (i < argc)
	{
		read_elevation(argv[i], &m);
		print_matrix(&m);
		free(m.v.d);
		i++;
	}
}

#include <stdio.h>

static void	print_matrix(t_matrix *m)
{
	size_t	i;
	size_t	elems;

	printf("Matrix at %p. %zu by %zu\n", m, m->rows, m->cols);
	elems = m->rows * m->cols;
	i = 0;
	while (i < elems)
	{
		if (i && !(i % m->cols))
			putchar('\n');
		printf("%-3d ", m->v.d[i]);
		i++;
	}
}
