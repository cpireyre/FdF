/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:08:29 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/05 12:05:08 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	dvd(t_transform *T, int width, int height)
{
	static t_v4i	direction;
	static t_v3i	rotation;

	if (!direction.x)
		direction.x = 1;
	if (!direction.y)
		direction.y = 1;
	if (!rotation.y)
		rotation.y = 1;
	T->rotation = v3i_add(T->rotation, rotation);
	T->offset.x += direction.x;
	T->offset.y += direction.y;
	if (T->offset.x >= width || T->offset.x <= 0)
	{
		direction.x *= -1;
		rotation.y *= -1;
	}
	if (T->offset.y >= height || T->offset.y <= 0)
	{
		direction.y *= -1;
		rotation.y *= -1;
	}
}
