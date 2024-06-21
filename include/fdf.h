/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:45:14 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/21 11:06:02 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "t_map.h"
# include "assign_colors.h"

int		build_map_from_file(const char *path, t_map *map, t_arena a);
int		render(t_map *map, const char *name);

#endif
