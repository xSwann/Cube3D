/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:15:16 by slatrech          #+#    #+#             */
/*   Updated: 2025/11/21 16:15:17 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	wich_key(char key, char *next, char ***target, t_scene *scene)
{
	if (key == 'N')
	{
		*next = 'O';
		*target = &scene->no_texture;
	}
	if (key == 'S')
	{
		*next = 'O';
		*target = &scene->so_texture;
	}
	if (key == 'W')
	{
		*next = 'E';
		*target = &scene->we_texture;
	}
	if (key == 'E')
	{
		*next = 'A';
		*target = &scene->ea_texture;
	}
}

void	handle_textures(char *line, int i, t_scene *scene, char key)
{
	char	*texture;
	char	**target;
	char	next;

	wich_key(key, &next, &target, scene);
	if (line[++i] != next)
	{
		free(line);
		free_scene_infos(scene);
		error_handler("Textures must be NO SO WE EA following by path");
	}
	free(*target);
	texture = sanitize_texture_line(line + i + 1);
	if (!texture)
	{
		free(line);
		free_scene_infos(scene);
		error_handler("Memory allocation failed");
	}
	if (!is_empty(texture))
		*target = texture;
}

void	import_configuration_line(char *line, t_scene *scene)
{
	int		i;
	char	current_key;

	i = 0;
	while (line[i] && (ft_isspace(line[i])))
		i++;
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
		|| line[i] == 'E' || line[i] == 'F' || line[i] == 'C')
	{
		current_key = line[i];
		import_colors(line, i, scene);
		if (line[i] == 'N')
			handle_textures(line, i, scene, 'N');
		else if (line[i] == 'S')
			handle_textures(line, i, scene, 'S');
		else if (line[i] == 'W')
			handle_textures(line, i, scene, 'W');
		else if (line[i] == 'E')
			handle_textures(line, i, scene, 'E');
		return ;
	}
	free(line);
	free_scene_infos(scene);
	error_handler("Need configurations lines before the map");
}
