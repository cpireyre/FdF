#ifndef RASTERIZE_H
# define RASTERIZE_H

# include "MLX42/MLX42.h"
# include "t_map.h"
# include "line.h"

extern void rasterize(mlx_image_t *image, t_map *map);
extern void	paint_background(mlx_image_t *image, uint32_t bgcolor);
extern uint32_t	interpolate_color(uint32_t start, uint32_t end, int curr, int steps);

typedef union u_color {
    struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    } ch;
    uint32_t value;
} t_color;

void	bresenham(mlx_image_t *image, t_line line);

#endif /* RASTERIZE_H */
