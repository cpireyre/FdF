/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:43:04 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/21 10:03:55 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "t_map.h"
#include "config.h"

static void	loop_hook(void *param);
void		move(mlx_t *m, t_projection *param);
void		draw(mlx_image_t *img, t_map *map);
void		paint_background(mlx_image_t *img, uint32_t bgcolor);

void	render(mlx_t *mlx, mlx_image_t *img, t_map *map)
{
	struct s_ptr	p;

	p.mlx = mlx;
	p.img = img;
	p.map = map;
	p.param.scale = 100;
	p.param.angle = 44.3F;
	p.param.offset_x = WIN_WIDTH / 3;
	p.param.offset_y = WIN_HEIGHT / 2;
	mlx_loop_hook(mlx, &loop_hook, &p);
	mlx_loop(mlx);
}

static void	loop_hook(void *ctx)
{
	struct s_ptr	*p;

	p = (struct s_ptr *)ctx;
	paint_background(p->img, 0x40463aff);
	move(p->mlx, &p->param);
	project(p->map, &p->param);
	draw(p->img, p->map);
	if (mlx_is_key_down(p->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(p->mlx);
}
