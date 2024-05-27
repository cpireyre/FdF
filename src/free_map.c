/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:18:06 by copireyr          #+#    #+#             */
/*   Updated: 2024/05/27 13:18:09 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "t_map.h"

void	free_map(t_map *map)
{
	while (map->rows--)
		free(map->points[map->rows]);
	free(map->points);
}
