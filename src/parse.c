/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:16:52 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/28 14:15:59 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_line	to_line(t_vector a, t_vector b);
static int		count_lines_in_file(const char *path);
static t_vector	**parse_file(int fd, t_map *map, t_arena a);
static t_vector	*tokenize(int fd, int row, t_map *map, t_arena a);
static int		count_words_in_line(const char *line);
static void	find_min_max_elevation(t_map *map, int *min, int *max);
static int	to_lines(t_map *map, t_line **l, t_arena a);
static void	assign_colors(t_map *map, uint32_t low_color, uint32_t high_color);

int	parse(const char *path, t_line **lines, t_arena a)
{
	int		fd;
	int		lines_in_file;
	t_map	map;

	lines_in_file = count_lines_in_file(path);
	if (lines_in_file < 1 || lines_in_file > 1000)
		return (ft_error(NULL, path));
	map.rows = lines_in_file;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_error(NULL, path));
	map.points = parse_file(fd, &map, a);
	if (!map.points)
		return (ft_error(NULL, "Bad map"));
	close(fd);
	assign_colors(&map, LOW_COLOR, HIGH_COLOR);
	return (to_lines(&map, lines, a));
}

static t_vector	**parse_file(int fd, t_map *map, t_arena a)
{
	int	i;
	int	cols;

	map->points = arena_calloc(a, (size_t)map->rows, sizeof(t_vector *));
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

static t_vector	*tokenize(int fd, int row, t_map *map, t_arena a)
{
	int			i;
	char		*line;
	char		*token;
	t_vector	*points;

	if (ft_gnl(fd, &line) == -1)
		return (NULL);
	map->cols = count_words_in_line(line);
	points = arena_calloc(a, (size_t)map->cols, sizeof(t_vector));
	if (!points)
	{
		ft_memdel((void **)&line);
		return (NULL);
	}
	i = 0;
	token = strtok((char *)line, " \n");
	while (i < map->cols)
	{
		points[i].x = i;
		points[i].y = row;
		points[i].z = ft_atoi(token);
		i++;
		token = strtok(NULL, " \n");
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

static int	to_lines(t_map *map, t_line **l, t_arena a)
{
	int			i;
	int			j;
	t_vector	curr;
	int			num_lines;
	int			k;
	t_line		*lines;

	num_lines = (map->rows - 1) * map->cols + (map->cols - 1) * map->rows;
	lines = arena_calloc(a, (size_t)num_lines, sizeof(t_line));
	if (!lines)
		return (0);
	i = 0;
	k = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			curr = map->points[i][j];
			if (i + 1 < map->rows)
			{
				lines[k++] = to_line(curr, map->points[i + 1][j]);
			}
			if (j + 1 < map->cols)
			{
				lines[k++] = to_line(curr, map->points[i][j + 1]);
			}
			j++;
		}
		i++;
	}
	*l = lines;
	return (num_lines);
}

static t_line	to_line(t_vector a, t_vector b)
{
	t_line	line;

	line.x0 = a.x;
	line.y0 = a.y;
	line.x1 = b.x;
	line.y1 = b.y;
	line.z0 = a.z;
	line.z1 = b.z;
	line.color0 = (uint32_t)a.c;
	line.color1 = (uint32_t)b.c;
	return (line);
}

static void	assign_colors(t_map *map, uint32_t low_color, uint32_t high_color)
{
	int		i;
	int		j;
	int		min;
	int		max;

	i = 0;
	find_min_max_elevation(map, &min, &max);
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			map->points[i][j].c = (int)interpolate_color(
					(uint32_t)low_color, (uint32_t)high_color,
					(double)map->points[i][j].z / (double)(max - min));
			j++;
		}
		i++;
	}
}

static void	find_min_max_elevation(t_map *map, int *min, int *max)
{
	int	i;
	int	j;

	i = 0;
	*min = map->points[0][0].z;
	*max = *min;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (*min > map->points[i][j].z)
				*min = map->points[i][j].z;
			if (*max < map->points[i][j].z)
				*max = map->points[i][j].z;
			j++;
		}
		i++;
	}
}
