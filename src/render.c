/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:43:04 by copireyr          #+#    #+#             */
/*   Updated: 2024/05/25 16:28:24 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"

static void	key_hooks(mlx_key_data_t key_data, void *param);

void	render(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(600, 480, "meme lib", true);
	mlx_key_hook(mlx, &key_hooks, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

static void	key_hooks(mlx_key_data_t key_data, void *param)
{
	if (key_data.key == MLX_KEY_ESCAPE)
		mlx_close_window((mlx_t *)param);
}
