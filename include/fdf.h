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
# include "render.h"
# include "t_map.h"

# define WIN_WIDTH 1440
# define WIN_HEIGHT 900

int		build_map_from_file(const char *path, t_map *map, t_arena a);
void	assign_colors(t_map *map, uint32_t low_color, uint32_t high_color);

struct s_mlx_with_img
{
	int			init_success;
	mlx_t		*mlx;
	mlx_image_t	*img;
};

#endif
