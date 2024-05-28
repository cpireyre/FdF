/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:31:32 by copireyr          #+#    #+#             */
/*   Updated: 2024/05/28 11:05:13 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MAP_H
# define T_MAP_H

# include <stddef.h>

typedef struct s_point
{
	int				elevation;
	unsigned int	pixel_x;
	unsigned int	pixel_y;
	unsigned int	color;
}					t_point;

typedef struct s_map
{
	t_point	**points;
	int		rows;
	int		cols;
}	t_map;

typedef struct s_projection
{
	float			scale;
	float			angle;
	unsigned int	offset_x;
	unsigned int	offset_y;
}	t_projection;

void	free_map(t_map *map);
void	project(t_map *map, t_projection *param);

#endif /* T_MAP_H */
