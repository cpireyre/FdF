/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:33:18 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/28 14:36:56 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include "parse.h"
# include "transform.h"
# include "clip.h"
# include "rasterize.h"

# define WIN_WIDTH	1280
# define WIN_HEIGHT	720

typedef struct s_render_context
{
	mlx_t			*mlx;
	t_line			*lines;
	int				num_lines;
	t_projection	param;
	uint32_t		bg_color;
	int				init_success;
	size_t			image_size_in_pixels;
	mlx_image_t		*img;
}				t_render_context;

typedef void	(*t_hook)(void*);

#endif /* MAIN_H */
