/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:08:29 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/02 13:27:32 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	dvd(t_transform *T, int width, int height)
{
	static t_v4i	direction;

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

void	toggle_dvd_mode(mlx_key_data_t keydata, t_render_context *ctx)
{
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		ctx->dvd_mode_on ^= 1;
}
