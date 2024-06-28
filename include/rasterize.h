/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:33:32 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/28 13:32:21 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RASTERIZE_H
# define RASTERIZE_H

# include "MLX42/MLX42.h"
# include "interpolate_color.h"
# include "libft.h"
# include "t_line.h"

extern void	rasterize(mlx_image_t *image, t_line line);

#endif /* RASTERIZE_H */
