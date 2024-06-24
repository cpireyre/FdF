/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:31:32 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/20 12:25:55 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MAP_H
# define T_MAP_H

# include "MLX42/MLX42.h"
# include <stddef.h>
# include "libft.h"

typedef struct s_map
{
	t_vector	**points;
	int			rows;
	int			cols;
}	t_map;

typedef struct s_projection
{
	double	scale;
	double	angle;
	int		offset_x;
	int		offset_y;
}	t_projection;

void	project(t_map *map, t_projection *param);

#endif /* T_MAP_H */
