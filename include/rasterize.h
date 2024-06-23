#ifndef RASTERIZE_H
# define RASTERIZE_H

# include "drawline.h"
# include "libft.h"

extern void rasterize(mlx_image_t *img, t_map *map);
extern void	paint_background(mlx_image_t *image, uint32_t bgcolor);

#endif /* RASTERIZE_H */
