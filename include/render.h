#ifndef RENDER_H
# define RENDER_H

# include "MLX42/MLX42.h"
# include "t_map.h"

typedef void (*t_rasterizer)(mlx_image_t *image, t_map *map);

typedef struct s_render_context
{
	mlx_t			*mlx;
	t_projection	param;
	mlx_image_t		*img;
	t_map			*map;
	t_rasterizer	rasterize;
	uint32_t		bg_color;
	int				init_success;
}				t_render_context;

extern void	render(t_render_context ctx, t_map *map);

typedef	void (*t_hook)(void*);

#endif /* RENDER_H */
