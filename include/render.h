/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:21:41 by copireyr          #+#    #+#             */
/*   Updated: 2024/08/09 16:11:24 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "transform.h"
# include <MLX42/MLX42.h>

typedef struct s_render_context
{
	int				*z_buffer;
	mlx_t			*mlx;
	t_line			*lines;
	int				num_lines;
	t_transform		t;
	uint32_t		bg_color;
	int				init_success;
	size_t			image_size_in_pixels;
	mlx_image_t		*img;
	int				dvd_mode_on;
	t_v2i			mouse_pos;
}				t_render_context;

#endif /* RENDER_H */
