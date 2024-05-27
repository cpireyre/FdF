/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:16:52 by copireyr          #+#    #+#             */
/*   Updated: 2024/05/27 13:17:57 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> /* TODO: delete this */
#include "t_map.h"
#include "libft.h"

static ssize_t	count_lines_in_file(const char *path);
static t_point	**parse_file(int fd, t_map *map);
static t_point	*tokenize(int fd, t_map *map);
static size_t	count_words_in_line(const char *line);

int	build_map_from_file(const char *path, t_map *map)
{
	int		fd;
	ssize_t	num_lines;

	num_lines = count_lines_in_file(path);
	if (num_lines < 1 || num_lines > 1000)
		return (ft_error(NULL, path));
	map->rows = (size_t)num_lines;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_error(NULL, path));
	map->points = parse_file(fd, map);
	if (!map->points)
		return (ft_error(NULL, "Bad map"));
	close(fd);
	return (0);
}

static t_point	**parse_file(int fd, t_map *map)
{
	size_t	i;
	size_t	cols;

	map->points = malloc(map->rows * sizeof(t_point *));
	if (!map->points)
		return (NULL);
	i = 0;
	cols = 0;
	while (i < map->rows)
	{
		map->points[i] = tokenize(fd, map);
		ft_dprintf(STDERR_FILENO, "\n");
		if (!cols)
			cols = map->cols;
		if (cols != map->cols || !map->points[i])
		{
			free_map(map);
			return (NULL);
		}
		i++;
	}
	return (map->points);
}

static t_point	*tokenize(int fd, t_map *map)
{
	size_t	i;
	char	*line;
	char	*token;
	t_point	*points;

	if (ft_gnl(fd, &line) == -1)
		return (NULL);
	map->cols = count_words_in_line(line);
	points = malloc(sizeof(t_point) * map->cols);
	if (!points)
	{
		ft_memdel((void **)&line);
		return (NULL);
	}
	i = 0;
	token = strtok((char *)line, " \n");
	while (i < map->cols)
	{
		ft_dprintf(STDERR_FILENO, "%d ", ft_atoi(token));
		points[i++].elevation = ft_atoi(token);
		token = strtok(NULL, " \n");
	}
	ft_memdel((void **)&line);
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
		ft_memdel((void **)&line);
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
		while (*line && ft_isspace(*line))
			line++;
		if (*line && !ft_isspace(*line))
			words++;
		while (*line && !ft_isspace(*line))
			line++;
	}
	return (words);
}
