#include "t_map.h"

#include <stdlib.h>

/* Bresenham */
void drawline(mlx_image_t *img, t_point begin, t_point end)
{
    int dx = abs((int)end.pixel_x - (int)begin.pixel_x);
    int dy = abs((int)end.pixel_y - (int)begin.pixel_y);
    int sx = (begin.pixel_x < end.pixel_x) ? 1 : -1;
    int sy = (begin.pixel_y < end.pixel_y) ? 1 : -1;
    int err = dx - dy;

    while (1)
	{
        mlx_put_pixel(img, begin.pixel_x, begin.pixel_y, 0xffffffff);
        if (begin.pixel_x == end.pixel_x
			&& begin.pixel_y == end.pixel_y)
			break;
        int e2 = 2 * err;
        if (e2 > -dy)
		{
            err -= dy;
            begin.pixel_x = (unsigned int)((int)begin.pixel_x + sx);
        }
        if (e2 < dx)
		{
            err += dx;
			begin.pixel_y = (unsigned int)((int)begin.pixel_y + sy);
        }
    }
}
