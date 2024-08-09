/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:33:18 by copireyr          #+#    #+#             */
/*   Updated: 2024/08/09 16:26:34 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include "render.h"
# include "parse.h"
# include "clip.h"
# include "rasterize.h"
# include "mouse.h"
# include <limits.h>

# define WIN_WIDTH	800
# define WIN_HEIGHT	600
# define FULLSCREEN	0
# define ROT_SPEED	3
# define MOVE_SPEED	5
# define ZOOM_SPEED	2

typedef void	(*t_hook)(void*);

void		serialize(t_transform T);
t_transform	deserialize(int default_width, int default_height);
void		dvd(t_transform *T, int width, int height);
void		move(mlx_t *m, t_transform *T);

#endif /* MAIN_H */
