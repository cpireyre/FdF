/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:18:24 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/02 13:37:44 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "t_line.h"
# include "interpolate_color.h"

typedef struct s_map
{
	t_v4i	**points;
	int			rows;
	int			cols;
}	t_map;

extern int		parse(const char *path, t_line **lines, t_arena a);
int				to_lines(t_map *map, t_line **l, t_arena a);
void			assign_colors(t_map *map, uint32_t locolor, uint32_t hicolor);

#endif /* PARSE_H */
