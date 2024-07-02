/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:08:29 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/02 11:17:59 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "transform.h"

void	dvd(t_transform *T, int width, int height)
{
	static t_vector	direction;

	if (!direction.x)
		direction.x = 1;
	if (!direction.y)
		direction.y = 1;
	if (!direction.z)
		direction.z = 1;
	T->offset_x += direction.x;
	T->offset_y += direction.y;
	if (T->offset_x == width || T->offset_x == 0)
		direction.x *= -1;
	if (T->offset_y == height || T->offset_y == 0)
		direction.y *= -1;
}
