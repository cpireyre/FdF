#ifndef RENDER_H
# define RENDER_H

#include "MLX42/MLX42.h"

typedef	void (*t_hook)(void*);

typedef struct s_render_context
{
	mlx_t			*mlx;
	t_projection	param;
	void			*img;
	t_map			*map;
}				t_render_context;

#endif /* RENDER_H */
