/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:43:04 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/14 10:17:13 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "t_map.h"
#include "config.h"

static void	loop_hook(void *param);
void		move(mlx_t *m, t_projection *param);
void		draw_points(mlx_image_t *img, t_map *map);

int	render(t_map *map, const char *name)
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	struct s_ptr	p;

	mlx_set_setting(MLX_HEADLESS, false);
	mlx = mlx_init(WIDTH, HEIGHT, name, false);
	if (!mlx)
		return (1);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		return (1);
	p.mlx = mlx;
	p.img = img;
	p.map = map;
	p.param.scale = 30;
	p.param.angle = 2.3F;
	p.param.offset_x = WIDTH / 3;
	p.param.offset_y = HEIGHT / 3;
	mlx_loop_hook(mlx, &loop_hook, &p);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (MLX_SUCCESS);
}

static void	loop_hook(void *ctx)
{
	struct s_ptr	*p;

	p = (struct s_ptr *)ctx;
	move(p->mlx, &p->param);
	project(p->map, &p->param);
	draw_points(p->img, p->map);
	if (mlx_is_key_down(p->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(p->mlx);
}
