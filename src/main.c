/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:45:09 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/21 11:30:45 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_render_context	initialize_mlx(const char *name, int width, int height);

int	main(int argc, char **argv)
{
	int						err;
	t_map					map;
	t_arena					a;
	t_render_context		ctx;

	if (argc == 2)
	{
		a = arena_new();
		if (!a)
			return (1);
		err = build_map_from_file(argv[1], &map, a);
		ctx = initialize_mlx(argv[1], WIN_WIDTH, WIN_HEIGHT);
		if (!err && ctx.init_success)
		{
			assign_colors(&map, 0xa6e36dff, 0xdb762eff);
			render(ctx.mlx, ctx.img, &map);
		}
		if (ctx.mlx)
			mlx_terminate(ctx.mlx);
		arena_dispose(&a);
	}
	else
		ft_printf("Usage: ./fdf map.fdf\n");
	return (0);
}

static t_render_context	initialize_mlx(const char *name, int width, int height)
{
	t_render_context	m;

	mlx_set_setting(MLX_FULLSCREEN, true);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	m.mlx = NULL;
	m.img = NULL;
	m.mlx = mlx_init(width, height, name, true);
	if (!m.mlx)
		return (m);
	m.img = mlx_new_image(m.mlx, (uint32_t)m.mlx->width, (uint32_t)m.mlx->height);
	if (!m.img)
		return (m);
	if (mlx_image_to_window(m.mlx, m.img, 0, 0) != -1)
		m.init_success = 1;
	return (m);
}
