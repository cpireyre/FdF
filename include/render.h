#ifndef RENDER_H
# define RENDER_H

#include "MLX42/MLX42.h"

typedef void (*plot_func_t)(void *img, int x, int y, uint32_t color);

typedef struct s_render_context
{
	mlx_t			*mlx;
	t_projection	param;
	void			*img;
	t_map			*map;
	plot_func_t		plot;
	int				quality;
}				t_render_context;

# define LOW 0
# define MEDIUM 1
# define HIGH 2

#endif /* RENDER_H */
