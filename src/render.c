/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:43:04 by copireyr          #+#    #+#             */
/*   Updated: 2024/05/25 16:37:07 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"

static void	key_hooks(mlx_key_data_t key_data, void *param);

void	render(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(600, 480, "FdF", true);
	if (!mlx)
		return (1);
	mlx_key_hook(mlx, &key_hooks, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}

static void	key_hooks(mlx_key_data_t key_data, void *param)
{
	if (key_data.key == MLX_KEY_ESCAPE)
		mlx_close_window((mlx_t *)param);
}
