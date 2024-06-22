/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:09:15 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/20 10:22:29 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_map.h"

void	move(mlx_t *m, t_projection *param)
{
	if (mlx_is_key_down(m, MLX_KEY_RIGHT_SHIFT))
	{
		param->scale -= 1 * (mlx_is_key_down(m, MLX_KEY_W));
		param->angle -= 0.1F * (mlx_is_key_down(m, MLX_KEY_A));
		param->scale += 1 * (mlx_is_key_down(m, MLX_KEY_S));
		param->angle += 0.1F * (mlx_is_key_down(m, MLX_KEY_D));
		if (param->scale < 0)
			param->scale = 0;
	}
	else
	{
		param->offset_y -= 5 * (mlx_is_key_down(m, MLX_KEY_W));
		param->offset_x -= 5 * (mlx_is_key_down(m, MLX_KEY_A));
		param->offset_y += 5 * (mlx_is_key_down(m, MLX_KEY_S));
		param->offset_x += 5 * (mlx_is_key_down(m, MLX_KEY_D));
	}
}
