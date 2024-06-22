#ifndef RENDER_H
# define RENDER_H

#include "MLX42/MLX42.h"

typedef void (*plot_func_t)(void *img, int x, int y, uint32_t color);

typedef struct s_render_context
{
	void		*img;
	plot_func_t	plot;
	int			width;
	int			height;
}				t_render_context;

#endif /* RENDER_H */
