/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:45:09 by copireyr          #+#    #+#             */
/*   Updated: 2024/07/04 11:27:17 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_render_context	initialize_ctx(const char *name, t_arena a);
static void				render_frame(t_render_context *ctx);
static void				move(mlx_t *m, t_transform *T);

int	main(int argc, char **argv)
{
	t_arena					a;
	t_render_context		ctx;

	if (argc == 2)
	{
		a = arena_new();
		if (!a)
			return (1);
		ctx = initialize_ctx(argv[1], a);
		ctx.num_lines = parse(argv[1], &ctx.lines, a);
		if (ctx.num_lines && ctx.init_success)
		{
			mlx_loop_hook(ctx.mlx, (t_hook)render_frame, &ctx);
			mlx_key_hook(ctx.mlx, (mlx_keyfunc)toggle_dvd_mode, &ctx);
			mlx_loop(ctx.mlx);
			serialize(ctx.t);
		}
		if (ctx.mlx)
			mlx_terminate(ctx.mlx);
		arena_dispose(&a);
	}
	else
		ft_dprintf(2, "Usage: ./fdf map.fdf\n");
	return (0);
}

static t_render_context	initialize_ctx(const char *name, t_arena a)
{
	t_render_context	ctx;

	ctx.dvd_mode_on = 0;
	ctx.z_buffer = arena_alloc(a, WIN_HEIGHT * WIN_WIDTH * sizeof(int));
	if (!ctx.z_buffer)
		return (ctx);
	ctx.init_success = 0;
	ctx.bg_color = BG_COLOR;
	ctx.t = deserialize(WIN_WIDTH, WIN_HEIGHT);
	mlx_set_setting(MLX_FULLSCREEN, FULLSCREEN);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	ctx.mlx = NULL;
	ctx.img = NULL;
	ctx.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, name, true);
	if (!ctx.mlx)
		return (ctx);
	ctx.img = mlx_new_image(ctx.mlx,
			WIN_WIDTH, WIN_HEIGHT);
	if (!ctx.img)
		return (ctx);
	ctx.image_size_in_pixels = ctx.img->width * ctx.img->height;
	if (mlx_image_to_window(ctx.mlx, ctx.img, 0, 0) != -1)
		ctx.init_success = 1;
	return (ctx);
}

static void	render_frame(t_render_context *ctx)
{
	t_line	current_line;
	t_line	*line;

	ft_memset_32(ctx->img->pixels, ctx->bg_color, ctx->image_size_in_pixels);
	ft_memset_32(ctx->z_buffer, (uint32_t)INT_MIN, WIN_WIDTH * WIN_HEIGHT);
	move(ctx->mlx, &ctx->t);
	if (ctx->dvd_mode_on)
		dvd(&ctx->t, WIN_WIDTH, WIN_HEIGHT);
	ctx->t.center = v3dd(0);
	line = ctx->lines - 1;
	while (++line != ctx->lines + ctx->num_lines)
		ctx->t.center = v3d_add(ctx->t.center, v3d_add(line->world0, line->world1));
	ctx->t.center = v3d_div(ctx->t.center, v3dd(2 * ctx->num_lines));
	while (line-- != ctx->lines)
	{
		current_line = transform(&ctx->t, *line);
		if (clip(&current_line, (int)ctx->img->width, (int)ctx->img->height))
			rasterize(ctx->img, ctx->z_buffer, current_line);
	}
	if (mlx_is_key_down(ctx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(ctx->mlx);
}

static int	check_key_pair(mlx_t *m, keys_t key0, keys_t key1)
{
	return (mlx_is_key_down(m, key0) - mlx_is_key_down(m, key1));
}

static void	move(mlx_t *m, t_transform *T)
{
	if (mlx_is_key_down(m, MLX_KEY_RIGHT_ALT))
		T->rotation = v3i_add(T->rotation,
				v3i(
					3 * check_key_pair(m, MLX_KEY_D, MLX_KEY_A),
					3 * check_key_pair(m, MLX_KEY_S, MLX_KEY_W),
					3 * check_key_pair(m, MLX_KEY_E, MLX_KEY_Q)
				   ));
	else if (mlx_is_key_down(m, MLX_KEY_RIGHT_SHIFT))
		T->scale = ft_max(3, T->scale + check_key_pair(m, MLX_KEY_W, MLX_KEY_S));
	else if (!mlx_is_key_down(m, MLX_KEY_RIGHT_SHIFT))
		T->offset = v2i_add(T->offset, v2i(
					5 * check_key_pair(m, MLX_KEY_D, MLX_KEY_A),
					5 * check_key_pair(m, MLX_KEY_S, MLX_KEY_W)
					));
	if (mlx_is_key_down(m, MLX_KEY_R))
	{
		ft_bzero(T, sizeof(*T));
		T->scale = 100;
		T->offset.y = m->height / 2;
		T->offset.x = m->width / 2;
	}
	T->cos_yaw = cos(T->rotation.x * M_PI / 180.0);
	T->sin_yaw = sin(T->rotation.x * M_PI / 180.0);
	T->cos_pitch = cos(T->rotation.y * M_PI / 180.0);
	T->sin_pitch = sin(T->rotation.y * M_PI / 180.0);
	T->cos_roll = cos(T->rotation.z * M_PI / 180.0);
	T->sin_roll = sin(T->rotation.z * M_PI / 180.0);
}
