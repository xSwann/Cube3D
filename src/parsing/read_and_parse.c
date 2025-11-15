#include "../../headers/cube3D.h"


void init_scene(t_scene *scene)
{
	scene->ceiling_color = NULL;
	scene->floor_color = NULL;
	scene->ea_texture = NULL;
	scene->so_texture = NULL;
	scene->no_texture = NULL;
	scene->we_texture = NULL;
	scene->map_struct = NULL;
}

t_scene	create_scene(char *scene_name)
{
	int		fd;
	t_scene	scene;
	int i;
    char **raw_map;

	i = 0;
	fd = open(scene_name, O_RDONLY);
	if (fd < 0)
		error_handler("File does not exist");
	init_scene(&scene);
	read_scene_lines(fd, &scene);
	raw_map= put_list_in_tabs(scene.map_struct, 1);
    get_width_and_height(raw_map, &scene);
    scene.map_tab = uniform_map(raw_map, scene.map_width, scene.map_height);
    free_tab(raw_map);
	return (scene);
}

t_scene parse_file(char *file_name)
{
    t_scene scene;

	scene = create_scene(file_name);
    validate_textures(&scene);
    validate_map(scene.map_tab, scene.map_width, scene.map_height);
    return (scene);
}