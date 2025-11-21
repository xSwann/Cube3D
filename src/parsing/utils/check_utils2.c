#include "../../../headers/cube3D.h"

int	have_good_extension(char *texture)
{
	int	len;

	len = ft_strlen(texture);
	if (len <= 4 || texture[len -4] != '.' || texture[len -3] != 'x'
		|| texture[len -2] != 'p' || texture[len -1] != 'm'
		|| texture[len] != '\0')
		return (0);
	return (1);
}

int	is_configuration_full(t_scene *scene)
{
	if (is_empty(scene->ceiling_color) || is_empty(scene->floor_color)
		|| is_empty(scene->no_texture) || is_empty(scene->so_texture)
		|| is_empty(scene->we_texture)
		|| is_empty(scene->ea_texture))
		return (0);
	return (1);
}
