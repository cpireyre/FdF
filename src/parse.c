/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:16:52 by copireyr          #+#    #+#             */
/*   Updated: 2024/08/08 19:53:00 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_v4i	**parse_file(char **file, t_map *map, t_arena a);
static t_v4i	*tokenize(char *line, int row, t_map *map, t_arena a);

int	parse(const char *path, t_line **lines, t_arena a)
{
	char	**file;
	t_map	map;
	t_arena	scratch;
	int		ret;

	ret = 0;
	scratch = arena_new();
	if (!scratch)
		return (!ft_dprintf(2, "error: can't alloc memory\n"));
	file = ft_arena_slurp(scratch, path);
	if (file)
	{
		map.rows = 0;
		while (file[map.rows])
			map.rows++;
		map.points = parse_file(file, &map, scratch);
		if (map.points && map.cols)
		{
			assign_colors(&map, LOW_COLOR, HIGH_COLOR);
			ret = to_lines(&map, lines, a);
		}
		else
			ft_dprintf(2, "error: invalid file\n");
	}
	arena_dispose(&scratch);
	return (ret);
}

static t_v4i	**parse_file(char **file, t_map *map, t_arena scratch)
{
	int	i;
	int	cols;

	map->points = arena_calloc(scratch, (size_t)map->rows, sizeof(t_v4i *));
	i = 0;
	cols = 0;
	map->cols = 0;
	while (map->points && i < map->rows)
	{
		map->points[i] = tokenize(file[i], i, map, scratch);
		if (!cols)
			cols = map->cols;
		if (cols != map->cols || !map->points[i])
			return (NULL);
		i++;
	}
	return (map->points);
}

uint32_t	atoc(char *str)
{
	static const char	*base = "0123456789ABCDEF0123456789abcdef";
	int					digits;
	uint32_t			color;

	digits = 0;
	color = 0;
	while (*str && ft_strchr(base, *str))
	{
		color = (uint32_t)(color * 16 + (ft_strchr(base, *str++) - base) % 16);
		digits++;
	}
	while (digits++ < 8)
		color = color * 16;
	color += 0xff;
	return (color);
}

t_v4i	read_z_and_color(char *tok)
{
	const size_t		example_color = ft_strlen(",0xFFFFFF");
	t_v4i				ret;
	char				*color_ptr;

	ret.z = ft_atoi(tok);
	color_ptr = ft_strchr(tok, ',');
	ret.c = 0;
	if (color_ptr && ft_strlen(color_ptr) == example_color)
		ret.c = (int)atoc(color_ptr + 3);
	return (ret);
}

static t_v4i	*tokenize(char *line, int row, t_map *map, t_arena scratch)
{
	int		i;
	char	*token;
	t_v4i	*points;

	map->cols = ft_count_tokens(line);
	points = arena_calloc(scratch, (size_t)map->cols, sizeof(t_v4i));
	if (!points)
		return (NULL);
	i = -1;
	token = ft_strtok((char *)line, " \t\v\n\r\f");
	while (++i < map->cols)
	{
		points[i] = read_z_and_color(token);
		points[i].x = i;
		points[i].y = row;
		token = ft_strtok(NULL, " \t\v\n\r\f");
	}
	return (points);
}
