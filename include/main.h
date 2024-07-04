/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:33:18 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/04 11:33:24 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include "parse.h"
# include "transform.h"
# include "clip.h"
# include "rasterize.h"
# include <limits.h>

# define WIN_WIDTH	100*16
# define WIN_HEIGHT	100*10
# define FULLSCREEN	true

typedef struct s_render_context
{
	int				*z_buffer;
	mlx_t			*mlx;
	t_line			*lines;
	int				num_lines;
	t_transform		transform;
	uint32_t		bg_color;
	int				init_success;
	size_t			image_size_in_pixels;
	mlx_image_t		*img;
	int				dvd_mode_on;
}				t_render_context;

typedef void	(*t_hook)(void*);

void		serialize(t_transform T);
t_transform	deserialize(int default_width, int default_height);
void		dvd(t_transform *T, int width, int height);
void		toggle_dvd_mode(mlx_key_data_t keydata, t_render_context *ctx);

#endif /* MAIN_H */
