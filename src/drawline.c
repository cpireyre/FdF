#include "rasterize.h"

void	bresenham(mlx_image_t *img, t_line line)
{
	int			i;
	int			err;
	uint32_t	color;
	int			double_err;

	i = 0;
	color = line.color0;
	err = line.delta_x + line.delta_y;
	while (i < line.length)
	{
		double_err = err * 2;
		mlx_put_pixel(img, (uint32_t)line.x0, (uint32_t)line.y0, color);
		color = interpolate_color(line.color0, line.color1, i, line.length);
		if (double_err > line.delta_y)
		{
			err += line.delta_y;
			line.x0 += line.slope_x;
		}
		if (double_err < line.delta_x)
		{
			err += line.delta_x;
			line.y0 += line.slope_y;
		}
		i++;
	}
	mlx_put_pixel(img, (uint32_t)line.x1, (uint32_t)line.y1, line.color1);
}
