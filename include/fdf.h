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
#include "config.h"

void	render(mlx_t *mlx, mlx_image_t *img, t_map *map);
int		build_map_from_file(const char *path, t_map *map, t_arena a);

struct s_mlx_with_img
{
	int			instance;
	mlx_t		*mlx;
	mlx_image_t	*img;
};

#endif
