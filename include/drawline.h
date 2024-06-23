#ifndef DRAWLINE_H
# define DRAWLINE_H

#include "libft.h"
#include "clip.h"
#include "t_map.h"
#include "config.h"
#include "t_tuple.h"
#include "draw.h"
#include "render.h"
#include "interpolate_color.h"

extern void	drawline(t_render_context *ctx, t_vec2 u, t_vec2 v, t_vec2 colors);

#endif /* DRAWLINE_H */
