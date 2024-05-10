#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include "vec.h"
#include "read_elevation.h"

static int	read_row(char *line, t_vec *v);
static int	is_space(int c);

int	read_elevation(const char *path, t_matrix *m)
{
	int	fd;
	char	*line;
	int	curr_cols;

	fd = open(path, O_RDONLY);
	ft_bzero(m, sizeof(*m));
	if (fd < 0 || initvec(&m->v))
		return (1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		m->rows++;
		curr_cols = read_row(line, &m->v);
		free(line);
		if (curr_cols == -1 || curr_cols == 0)
		{
			free(m->v.d);
			return (1);
		}
		if (!m->cols)
			m->cols = curr_cols;
		else if ((int)m->cols != curr_cols)
		{
			ft_putendl_fd("Unexpected number of entries", 2);
			free(m->v.d);
			return (1);
		}
	}
	close(fd);
	return (0);
}

static int	read_row(char *line, t_vec *v)
{
	int	cols;

	cols = 0;
	while (*line)
	{
		while (*line && is_space(*line))
			line++;
		if (*line)
		{
			if (pushvec(v, ft_atoi(line)))
				return (-1);
			cols++;
		}
		while (*line && !is_space(*line))
			line++;
	}
	return (cols);
}

static int	is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}
