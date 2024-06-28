/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:33:32 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/28 11:30:01 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RASTERIZE_H
# define RASTERIZE_H

# include <math.h>
# include "MLX42/MLX42.h"
# include "t_map.h"
# include "interpolate_color.h"
# include "libft.h"
# include "line.h"

extern void	rasterize(mlx_image_t *image, t_line line);

int			clip(t_line *line, int xmax, int ymax);

typedef int	t_clip_code;

enum e_clip_code
{
	INSIDE = 0,
	LEFT = 1,
	RIGHT = 2,
	BOTTOM = 4,
	TOP = 8
};

#endif /* RASTERIZE_H */
