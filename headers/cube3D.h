#ifndef CUBE3D_H
# define CUBE3D_H

/*===INCLUDES===*/

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
# include "../src/get_next_line/get_next_line.h"

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

/*===FUNCTIONS===*/

t_scene parse_file(char *file_name);


#endif