/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:45:09 by copireyr          #+#    #+#             */
/*   Updated: 2024/05/28 11:24:25 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	int		i;
	int		err;
	t_map	map;
	t_arena	a;

	i = 1;
	while (i < argc)
	{
		a = arena_new();
		if (!a)
			return (1);
		err = build_map_from_file(argv[i], &map, a);
		if (!err)
			render(&map, argv[i]);
		i++;
		arena_dispose(&a);
	}
	return (0);
}
