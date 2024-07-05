/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:11:00 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/05 12:39:49 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		get_zoom_delta(mlx_t *m);
static t_v2i	get_offset_delta(mlx_t *m);
static t_v3i	get_rotation_delta(mlx_t *m);

void	move(mlx_t *m, t_transform *T)
{
	t_v3i	rotation_delta;
	t_v2i	offset_delta;
	int		zoom_delta;

	if (mlx_is_key_down(m, MLX_KEY_RIGHT_SHIFT))
	{
		zoom_delta = get_zoom_delta(m);
		T->scale = ft_max(T->scale + zoom_delta, 3);
	}
	else if (mlx_is_key_down(m, MLX_KEY_RIGHT_ALT))
	{
		rotation_delta = get_rotation_delta(m);
		T->rotation = v3i_add(T->rotation, rotation_delta);
	}
	else
	{
		offset_delta = get_offset_delta(m);
		T->offset = v2i_add(T->offset, offset_delta);
	}
	T->cos_yaw = cos(T->rotation.x * M_PI / 180.0);
	T->sin_yaw = sin(T->rotation.x * M_PI / 180.0);
	T->cos_pitch = cos(T->rotation.y * M_PI / 180.0);
	T->sin_pitch = sin(T->rotation.y * M_PI / 180.0);
	T->cos_roll = cos(T->rotation.z * M_PI / 180.0);
	T->sin_roll = sin(T->rotation.z * M_PI / 180.0);
}

static int	get_zoom_delta(mlx_t *m)
{
	int	zoom_delta;

	zoom_delta = 0;
	zoom_delta += mlx_is_key_down(m, MLX_KEY_W);
	zoom_delta -= mlx_is_key_down(m, MLX_KEY_S);
	return (zoom_delta * ZOOM_SPEED);
}

static t_v2i	get_offset_delta(mlx_t *m)
{
	t_v2i	offset_delta;

	offset_delta = v2i(0, 0);
	offset_delta.x += mlx_is_key_down(m, MLX_KEY_D);
	offset_delta.x -= mlx_is_key_down(m, MLX_KEY_A);
	offset_delta.y += mlx_is_key_down(m, MLX_KEY_S);
	offset_delta.y -= mlx_is_key_down(m, MLX_KEY_W);
	return (v2i_mul(offset_delta, v2i(MOVE_SPEED, MOVE_SPEED)));
}

static t_v3i	get_rotation_delta(mlx_t *m)
{
	t_v3i	rotation_delta;

	rotation_delta = v3ii(0);
	rotation_delta.x += mlx_is_key_down(m, MLX_KEY_D);
	rotation_delta.x -= mlx_is_key_down(m, MLX_KEY_A);
	rotation_delta.y += mlx_is_key_down(m, MLX_KEY_S);
	rotation_delta.y -= mlx_is_key_down(m, MLX_KEY_W);
	rotation_delta.z += mlx_is_key_down(m, MLX_KEY_E);
	rotation_delta.z -= mlx_is_key_down(m, MLX_KEY_Q);
	return (v3i_mul(rotation_delta, v3ii(ROT_SPEED)));
}
