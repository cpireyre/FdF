#include "rasterize.h"

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
	t_vec2	u;
	t_vec2	v;
	t_vec2	colors;

	u.x = a.pixel_x;
	u.y = a.pixel_y;
	v.x = b.pixel_x;
	v.y = b.pixel_y;
	colors.x = (int)a.color;
	colors.y = (int)b.color;
	drawline(img, u, v, colors);
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

