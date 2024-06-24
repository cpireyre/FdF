#ifndef RASTERIZE_H
# define RASTERIZE_H

# include <math.h>
# include "MLX42/MLX42.h"
# include "t_map.h"
# include "color_lerp.h"
# include "libft.h"

extern void rasterize(mlx_image_t *image, t_map *map);

typedef struct s_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	int			length;
	int			delta_x;
	int			delta_y;
	int			slope_x;
	int			slope_y;
	uint32_t	color0;
	uint32_t	color1;
}				t_line;

int	clip(t_line *line, int xmax, int ymax);

typedef int	t_clip_outcode;

enum e_clip_outcode
{
	INSIDE = 0,
	LEFT = 1,
	RIGHT = 2,
	BOTTOM = 4,
	TOP = 8
};

#endif /* RASTERIZE_H */
