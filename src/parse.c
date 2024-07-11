/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:16:52 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/11 15:11:02 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int		count_lines_in_file(const char *path);
static t_v4i	**parse_file(int fd, t_map *map, t_arena a);
static t_v4i	*tokenize(int fd, int row, t_map *map, t_arena a);
static int		count_words_in_line(const char *line);

int	parse(const char *path, t_line **lines, t_arena a)
{
	int		fd;
	int		lines_in_file;
	t_map	map;

	lines_in_file = count_lines_in_file(path);
	if (lines_in_file < 1 || lines_in_file > 1000)
	{
		ft_error(NULL, path);
		return (0);
	}
	map.rows = lines_in_file;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_error(NULL, path));
	map.points = parse_file(fd, &map, a);
	if (!map.points)
	{
		ft_error(NULL, "Bad map");
		return (0);
	}
	close(fd);
	assign_colors(&map, LOW_COLOR, HIGH_COLOR);
	return (to_lines(&map, lines, a));
}

static t_v4i	**parse_file(int fd, t_map *map, t_arena a)
{
	int	i;
	int	cols;

	map->points = arena_calloc(a, (size_t)map->rows, sizeof(t_v4i *));
	if (!map->points)
		return (NULL);
	i = 0;
	cols = 0;
	while (i < map->rows)
	{
		map->points[i] = tokenize(fd, i, map, a);
		if (!cols)
			cols = map->cols;
		if (cols != map->cols || !map->points[i])
			return (NULL);
		i++;
	}
	return (map->points);
}

static t_v4i	*tokenize(int fd, int row, t_map *map, t_arena a)
{
	int		i;
	char	*line;
	char	*token;
	t_v4i	*points;

	if (ft_gnl(fd, &line) == -1)
		return (NULL);
	map->cols = count_words_in_line(line);
	points = arena_calloc(a, (size_t)map->cols, sizeof(t_v4i));
	if (!points)
	{
		ft_memdel((void **)&line);
		return (NULL);
	}
	i = -1;
	token = ft_strtok((char *)line, " \t\v\n\r\f");
	while (++i < map->cols)
	{
		points[i].x = i;
		points[i].y = row;
		points[i].z = ft_atoi(token);
		token = ft_strtok(NULL, " \t\v\n\r\f");
	}
	ft_memdel((void **)&line);
	return (points);
}

static int	count_lines_in_file(const char *path)
{
	int		fd;
	ssize_t	ret;
	char	*line;
	int		num_lines;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	num_lines = 0;
	while (1)
	{
		ret = ft_gnl(fd, &line);
		if (line && ft_strlen(line) < 2)
		{
			ft_memdel((void **)&line);
			return (-1);
		}
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

static int	count_words_in_line(const char *line)
{
	int	words;

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
