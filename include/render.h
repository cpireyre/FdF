#ifndef RENDER_H
# define RENDER_H

# include "MLX42/MLX42.h"
# include "t_map.h"
# include "rasterize.h"

typedef	void (*t_hook)(void*);

typedef struct s_render_context
{
	mlx_t			*mlx;
	t_projection	param;
	mlx_image_t		*img;
	t_map			*map;
	int				init_success;
}				t_render_context;

extern void	render(mlx_t *mlx, mlx_image_t *img, t_map *map);

#endif /* RENDER_H */
