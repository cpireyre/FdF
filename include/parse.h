/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:18:24 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/28 13:37:06 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <fcntl.h>
# include <unistd.h>
# include <string.h> /* TODO: delete this */
# include "libft.h"
# include "t_line.h"
# include "interpolate_color.h"

typedef struct s_map
{
	t_vector	**points;
	int			rows;
	int			cols;
}	t_map;

int	parse(const char *path, t_line **lines, t_arena a);
extern void		assign_colors(t_map *map, uint32_t lo_color, uint32_t hi_color);

#endif /* PARSE_H */
