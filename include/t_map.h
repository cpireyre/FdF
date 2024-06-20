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

typedef struct s_point
{
	int			pixel_x;
	int			pixel_y;
	int			elevation;
	uint32_t	color;
}					t_point;

typedef struct s_map
{
	t_point	**points;
	int		rows;
	int		cols;
}	t_map;

typedef struct s_projection
{
	float	scale;
	float	angle;
	int		offset_x;
	int		offset_y;
}	t_projection;

struct s_ptr
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_map			*map;
	t_projection	param;
};

void	project(t_map *map, t_projection *param);

#endif /* T_MAP_H */
