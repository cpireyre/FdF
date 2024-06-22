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

static struct s_mlx_with_img	initialize_mlx(const char *name);

int	main(int argc, char **argv)
{
	int						err;
	t_map					map;
	t_arena					a;
	struct s_mlx_with_img	m;

	if (argc == 2)
	{
		a = arena_new();
		if (!a)
			return (1);
		err = build_map_from_file(argv[1], &map, a);
		m = initialize_mlx(argv[1]);
		if (!err && m.instance != -1)
		{
			assign_colors(&map, 0xa6e36dff, 0xdb762eff);
			render(m.mlx, m.img, &map);
		}
		if (m.mlx)
			mlx_terminate(m.mlx);
		arena_dispose(&a);
	}
	else
		ft_printf("Usage: ./fdf map.fdf\n");
	return (0);
}

static struct s_mlx_with_img	initialize_mlx(const char *name)
{
	struct s_mlx_with_img	m;

	m.mlx = NULL;
	m.img = NULL;
	m.instance = -1;
	m.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, name, false);
	if (!m.mlx)
		return (m);
	m.img = mlx_new_image(m.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!m.img)
		return (m);
	m.instance = mlx_image_to_window(m.mlx, m.img, 0, 0);
	return (m);
}
