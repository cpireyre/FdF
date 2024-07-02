/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:33:18 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/02 11:19:13 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include "parse.h"
# include "transform.h"
# include "clip.h"
# include "rasterize.h"

# define RES		100
# define WIN_WIDTH	16
# define WIN_HEIGHT	9

typedef struct s_render_context
{
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

#endif /* MAIN_H */
