#include "mouse.h"

static void	mouse_scroll_zoom(double xdelta, double ydelta, t_transform *transform);

void	mouse_hooks_set(t_render_context *ctx)
{
	mlx_scroll_hook(ctx->mlx, (mlx_scrollfunc)&mouse_scroll_zoom, &ctx->t);
}

static void	mouse_scroll_zoom(double xdelta, double ydelta, t_transform *transform)
{
	transform->scale += (int)round(ydelta);
	if (transform->scale < 1)
		transform->scale = 1;
	(void)xdelta;
}

void drag(t_render_context *ctx)
{
	t_v2i	mouse_pos_current;
	t_v2i	mouse_pos_delta;

	mlx_get_mouse_pos(ctx->mlx, &mouse_pos_current.x, &mouse_pos_current.y);
	mouse_pos_delta = v2i_sub(mouse_pos_current, ctx->mouse_pos);
	if (mlx_is_mouse_down(ctx->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		ctx->t.offset = v2i_add(ctx->t.offset, mouse_pos_delta);
	}
	else if (mlx_is_mouse_down(ctx->mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		ctx->t.rotation.x += mouse_pos_delta.x;
		ctx->t.rotation.y += mouse_pos_delta.y;
	}
	mlx_get_mouse_pos(ctx->mlx, &ctx->mouse_pos.x, &ctx->mouse_pos.y);
}
