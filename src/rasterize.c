#include "rasterize.h"
#include "libft.h"

static void	connect(mlx_image_t *img, t_point a, t_point b);

void rasterize(mlx_image_t *img, t_map *map)
{
	int		i;
	int		j;
	t_point	curr;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			curr = map->points[i][j];
			if (i + 1 < map->rows)
				connect(img, curr, map->points[i + 1][j]);
			if (j + 1 < map->cols)
				connect(img, curr, map->points[i][j + 1]);
			j++;
		}
		i++;
	}
}

static void	connect(mlx_image_t *img, t_point a, t_point b)
{
	t_line		line;

	line.x0 = a.pixel_x;
	line.y0 = a.pixel_y;
	line.x1 = b.pixel_x;
	line.y1 = b.pixel_y;
	line.color0 = a.color;
	line.color1 = b.color;
	if (clip(&line, (int)img->width, (int)img->height))
	{
		line.delta_x = ft_abs(line.x1 - line.x0);
		line.delta_y = -ft_abs(line.y1 - line.y0);
		line.slope_x = ft_sign(line.x0, line.x1);
		line.slope_y = ft_sign(line.y0, line.y1);
		line.length = ft_max(line.delta_x, -line.delta_y);
		bresenham(img, line);
	}
}

void	paint_background(mlx_image_t *image, uint32_t bgcolor)
{
	int	i;
	int	j;

	i = 0;
	while ((uint32_t)i < image->width)
	{
		j = 0;
		while ((uint32_t)j < image->height)
		{
			mlx_put_pixel(image, (uint32_t)i, (uint32_t)j, bgcolor);
			j++;
		}
		i++;
	}
}

