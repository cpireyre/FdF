#include "fdf.h"

void	test_file_stuff(const char *path)
{
	char	**lines;
	size_t	i;

	ft_putendl_fd((char*)path, 1);
	lines = read_lines(path);
	if (lines)
	{
		i = 0;
		while (lines[i])
			ft_putendl_fd(lines[i++], 1);
		i = 0;
		while (lines[i])
			free(lines[i++]);
		free(lines);
	}
}

int	main(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		test_file_stuff(argv[i]);
		ft_putendl_fd("done", 1);
		i++;
	}
}
