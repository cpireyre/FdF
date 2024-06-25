#include "rasterize.h"
#include "libft.h"

static void	connect(mlx_image_t *img, t_vector a, t_vector b);
static void	bresenham(mlx_image_t *img, t_line line);

void rasterize(mlx_image_t *image, t_map *map)
{
	int	i;
	int	j;
	t_vector	curr;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			curr = map->points[i][j];
			if (i + 1 < map->rows)
				connect(image, curr, map->points[i + 1][j]);
			if (j + 1 < map->cols)
				connect(image, curr, map->points[i][j + 1]);
			j++;
		}
		i++;
	}
}

static void connect(mlx_image_t *img, t_vector a, t_vector b)
{
    t_line line;

    line.x0 = a.x;
    line.y0 = a.y;
    line.x1 = b.x;
    line.y1 = b.y;
    line.color0 = (uint32_t)a.c;
    line.color1 = (uint32_t)b.c;

    // Original line length
    double original_length = ft_distance(a.x, a.y, b.x, b.y);

    if (clip(&line, (int)img->width, (int)img->height)) {

        // Calculate the proportions
        double start_proportion = ft_distance(a.x, a.y, line.x0, line.y0) / original_length;
        double end_proportion = ft_distance(a.x, a.y, line.x1, line.y1) / original_length;

        // Interpolate the colors
        line.color0 = interpolate_color((uint32_t)a.c, (uint32_t)b.c, start_proportion);
        line.color1 = interpolate_color((uint32_t)a.c, (uint32_t)b.c, end_proportion);

        line.delta_x = ft_abs(line.x1 - line.x0);
        line.delta_y = -ft_abs(line.y1 - line.y0);
        line.slope_x = ft_sign(line.x0, line.x1);
        line.slope_y = ft_sign(line.y0, line.y1);
        line.length = ft_max(line.delta_x, -line.delta_y);
        bresenham(img, line);
    }
}

static void	bresenham(mlx_image_t *img, t_line line)
{
	int			i;
	int			err;
	uint32_t	color;
	int			double_err;

	i = 0;
	color = line.color0;
	err = line.delta_x + line.delta_y;
	while (line.x0 != line.x1 || line.y0 != line.y1)
	{
		double_err = err * 2;
		mlx_put_pixel(img, (uint32_t)line.x0, (uint32_t)line.y0, color);
		color = interpolate_color(line.color0, line.color1, (double)i/(double)line.length);
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
