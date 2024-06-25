#ifndef RASTERIZE_H
# define RASTERIZE_H

# include <math.h>
# include "MLX42/MLX42.h"
# include "t_map.h"
# include "interpolate_color.h"
# include "libft.h"
# include "line.h"

extern void rasterize(mlx_image_t *image, t_map *map);

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
