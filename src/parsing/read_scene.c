#include "../../headers/cube3D.h"

char	*read_configuration(char *scene_line, t_scene *scene, int fd)
{
	while (scene_line && !is_configuration_full(scene))
	{
		free(scene_line);
		scene_line = get_next_line(fd);
		remove_endl(&scene_line);
		if (scene_line && !is_empty(scene_line))
			import_configuration_line(scene_line, scene);
	}
	free(scene_line);
	scene_line = get_next_line(fd);
	remove_endl(&scene_line);
	while (scene_line && is_empty(scene_line))
	{
		free(scene_line);
		scene_line = get_next_line(fd);
		remove_endl(&scene_line);
		if (!scene_line)
		{
			free_scene(scene);
			error_handler("You should enter a map");
		}
	}
	return (scene_line);
}

char	*read_map(char *scene_line, t_scene *scene, int fd)
{
	while (scene_line && !is_empty(scene_line))
	{
		put_map_in_list(scene_line, scene);
		free(scene_line);
		scene_line = get_next_line(fd);
		remove_endl(&scene_line);
	}
	if (!scene->map_struct)
	{
		free_scene(scene);
		error_handler("You should enter a map");
	}
	while (scene_line)
	{
		free(scene_line);
		scene_line = get_next_line(fd);
		remove_endl(&scene_line);
		if (scene_line && !is_empty(scene_line))
		{
			free_scene(scene);
			free(scene_line);
			error_handler("Map must be the last parameter");
		}
	}
	return (scene_line);
}

void	read_scene_lines(int fd, t_scene *scene)
{
	char	*scene_line;

	(void)scene;
	scene_line = ft_strdup("debut");
	scene_line = read_configuration(scene_line, scene, fd);
	scene_line = read_map(scene_line, scene, fd);
	free(scene_line);
}
