#ifndef CUBE3D_H
# define CUBE3D_H

/*===INCLUDES===*/

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
# include "../src/get_next_line/get_next_line.h"
# include <math.h>

/*===STRUCTURES===*/

typedef struct s_list
{
	char			*line;
	struct s_list	*next;
}	t_list;

typedef struct s_scene
{
    t_list  *map_struct;
	char    **map_tab;
    char *no_texture;
    char *so_texture;
    char *we_texture;
    char *ea_texture;
    char *floor_color;
    char *ceiling_color;

}	t_scene;

/*
typedef struct s_map_data
{
	int		fd;
	int		line_counter;
	char		*path;
	char		**file;
	int		height;
	int		width;
	int		index_end;
}	t_map_data;
*/

/*=== STRUCTURES pour initialiser mlx et RayCaster ===*/

typedef struct s_texture_data
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	int		*floor;
	int		*ceiling;
}	t_texture_data;

typedef struct s_img
{
	void	*img;
	int	*addr;
	int	pixel_bits;
	int	size_line;
	int	endian;
}	t_img;

typedef struct s_ray
{

}

typedef struct s_player
{
	char		dir;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
} t_player

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int		win_height;
	int		win_width;
	t_map_data		map_data;
	char		**map;
	t_player	player;
	t_ray		ray;
	int		**texture_pixels;
	int		**textures;
	t_texture_data	texture_data;
}	t_data;

/*===FUNCTIONS===*/

t_scene parse_file(char *file_name);


#endif
