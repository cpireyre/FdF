/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arena_slurp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:34:46 by copireyr          #+#    #+#             */
/*   Updated: 2024/08/07 11:32:59 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**read_lines(t_arena arena, const int fd);

char	**ft_arena_slurp(t_arena arena, const char *path)
{
	const int	fd = open(path, O_RDONLY);
	char		**ret;

	if (fd == -1)
	{
		ft_dprintf(2, "error: can't open %s\n", path);
		return (NULL);
	}
	ret = read_lines(arena, fd);
	close(fd);
	if (!ret)
		ft_dprintf(2, "error: can't allocate memory\n");
	return (ret);
}

static char	**read_lines(t_arena arena, const int fd)
{
	char		**tmp;
	char		**lines;
	size_t		max_lines;
	size_t		num_lines;

	num_lines = 0;
	max_lines = 0;
	lines = NULL;
	while (1)
	{
		if (num_lines == max_lines)
		{
			max_lines = max_lines * 2 + (max_lines == 0) * FT_INITIAL_SIZE;
			tmp = arena_calloc(arena, 1, sizeof(char *) * max_lines);
			if (!tmp)
				return (NULL);
			if (lines)
				ft_memcpy(tmp, lines, sizeof(char *) * num_lines);
			lines = tmp;
		}
		lines[num_lines] = arena_gnl(arena, fd);
		if (!lines[num_lines++])
			break ;
	}
	return (lines);
}
