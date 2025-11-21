#include "../../headers/cube3D.h"

void	validate_texture(char *path, t_scene *scene)
{
	int	len;
	int	fd;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		free_scene_and_exit(scene, "Texture must end with .xpm");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		free_scene_and_exit(scene, "Texture file cannot be opened");
	close(fd);
}

void	validate_textures(t_scene *scene)
{
	validate_texture(scene->ea_texture, scene);
	validate_texture(scene->no_texture, scene);
	validate_texture(scene->so_texture, scene);
	validate_texture(scene->we_texture, scene);
}
