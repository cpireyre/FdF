/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:33:18 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/05 12:11:27 by copireyr         ###   ########.fr       */
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

# define WIN_WIDTH	4*320
# define WIN_HEIGHT	4*200
# define FULLSCREEN	false
# define ROT_SPEED	6
# define MOVE_SPEED	5
# define ZOOM_SPEED	2

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
}				t_render_context;

typedef void	(*t_hook)(void*);

void		serialize(t_transform T);
t_transform	deserialize(int default_width, int default_height);
void		dvd(t_transform *T, int width, int height);
void		move(mlx_t *m, t_transform *T);

#endif /* MAIN_H */
