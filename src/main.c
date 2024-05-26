/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:45:09 by copireyr          #+#    #+#             */
/*   Updated: 2024/05/23 11:51:03 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	int		i;
	int		err;
	t_map	map;

	i = 1;
	while (i < argc)
	{
		err = build_map_from_file(argv[i], &map);
		if (!err)
		{
			render(&map, argv[i]);
			free_map(&map);
		}
		i++;
	}
	return (0);
}
