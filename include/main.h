#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include "rasterize.h"
# include "t_map.h"

# define WIN_WIDTH	1280
# define WIN_HEIGHT	800
# define LOW_COLOR	0xa6e36dff
# define HIGH_COLOR	0xdb762eff
/* BG_COLOR needs different endianness because we write it to memory directly */
# define BG_COLOR	0xff3a4640

typedef struct s_render_context
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_map			*map;
	t_projection	param;
	uint32_t		bg_color;
	int				init_success;
	size_t			image_size_in_bytes;
}				t_render_context;

typedef	void (*t_hook)(void*);

int		build_map_from_file(const char *path, t_map *map, t_arena a);
void	assign_colors(t_map *map, uint32_t low_color, uint32_t high_color);

#endif /* MAIN_H */
