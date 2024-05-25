#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> /* TODO: delete this */
#include "t_map.h"
#include "libft.h"

static ssize_t	count_lines_in_file(const char *path);
static size_t	count_words_in_line(const char *line);
static t_point	*parse_line(char *line, size_t cols);

t_map	*parse_file(const char *path)
{
	int		fd;
	size_t	i;
	ssize_t	ret;
	t_map	*map;
	size_t	cols;
	char	*line;
	ssize_t	num_lines;

	num_lines = count_lines_in_file(path);
	ft_dprintf(STDERR_FILENO, "LOG: Parsing %d lines.\n", num_lines);
	map = malloc(sizeof(t_map));
	if (!map || num_lines < 1 || num_lines > 1000)
		return (NULL);
	map->rows = (size_t)num_lines;
	map->points = malloc(map->rows * sizeof(map->points));
	if (!map->points)
	{
		free(map);
		return (NULL);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		free(map->points);
		free(map);
		return (NULL);
	}
	i = 0;
	while (i < (size_t)num_lines)
	{
		ret = ft_gnl(fd, &line);
		if (ret == -1)
		{
			free(map->points);
			free(map);
			return (NULL);
		}
		if (!cols)
		{
			cols = count_words_in_line(line);
			map->cols = cols;
		}
		map->points[i] = parse_line(line, cols);
		ft_memdel((void**)&line);
		i++;
	}
	close(fd);
	return (map);
}

static t_point	*parse_line(char *line, size_t cols)
{
	size_t	i;
	char	*token;
	t_point	*points;
	int		elevation;

	points = malloc(sizeof(t_point) * cols);
	token = strtok((char *)line, " "); /* TODO: add to libft */
	i = 0;
	while (i < cols)
	{
		elevation = ft_atoi(token);
		ft_dprintf(STDERR_FILENO, "%d ", elevation);
		points[i++].elevation = elevation;
		token = strtok(NULL, " ");
	}
	ft_dprintf(STDERR_FILENO, "\n");
	return (points);
}

static ssize_t	count_lines_in_file(const char *path)
{
	int		fd;
	ssize_t	ret;
	char	*line;
	ssize_t	num_lines;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	num_lines = 0;
	while (1)
	{
		ret = ft_gnl(fd, &line);
		ft_memdel((void**)&line);
		if (ret == 0 || ret == -1)
			break ;
		num_lines++;
	}
	close(fd);
	if (ret == -1)
		return (-1);
	return (num_lines);
}

static size_t	count_words_in_line(const char *line)
{
	size_t	words;

	words = 0;
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (*line)
			words++;
		while (*line && *line != ' ')
			line++;
	}
	return (words);
}
