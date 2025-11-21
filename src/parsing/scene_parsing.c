#include "../../headers/cube3D.h"

//Les color lines ressortent sous le format "255,255,255"
// peut importe si l'user entre des espaces avant, apres
// ou entre les nombres et les virgules
char	*sanitize_color_line(char *line)
{
	int		i;
	char	*str;
	int		start;
	char	*sub;
	char	*new_str;

	i = 0;
	start = 0;
	str = NULL;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		start = i;
		while (line[i] && !ft_isspace(line[i]))
			i++;
		sub = ft_substr(line, start, i - start);
		new_str = ft_strjoin(str, sub);
		free(str);
		free(sub);
		str = ft_strdup(new_str);
		free(new_str);
	}
	return (str);
}

//Les textures peuvent etre avec des espaces entre les mots
//Ex: "file  name" est un nom de fichier valide et possible pour un fichier
//L'user doit rentrer le nom du fichier exact
char	*sanitize_texture_line(char *line)
{
	int		i;
	char	*str;
	int		start;
	char	*sub;
	int		end;

	i = 0;
	start = 0;
	end = ft_strlen(line) -1;
	str = NULL;
	while (line[i] && ft_isspace(line[i]))
		i++;
	while (ft_isspace(line[end]))
		end--;
	while (line[i] && i < end)
	{
		start = i;
		while (line[i] && i < end)
			i++;
		sub = ft_substr(line, start, end + 1 - start);
		str = ft_strjoin(str, sub);
		free(sub);
	}
	return (str);
}

//Retourne une ligne sanitize, si elle respecte le format imposee
char	*import_color_line( t_scene *scene, char *line, char *line_to_free)
{
	int		i;
	int		first_number;
	int		last_number;
	int		count;
	int		comma_count;
	char	*full_number;

	i = 0;
	count = 0;
	first_number = 0;
	comma_count = 0;
	last_number = 0;
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		first_number = i;
		count = 0;
		while (line[i] && ft_isdigit(line[i]))
		{
			i++;
			count++;
		}
		last_number = i;
		while (line[i] && ft_isspace(line[i]))
			i++;
		full_number = ft_substr(line, first_number, last_number - first_number);
		if (!full_number)
		{
			free_scene_infos(scene);
			free(line);
			free(line_to_free);
			error_handler("Memory allocation failed");
		}
		if ((line[i] == ',' && comma_count == 2) || count == 0
			|| (count > 3) || (ft_atoi(full_number) > 255))
		{
			free_scene_infos(scene);
			free(full_number);
			free(line);
			free(line_to_free);
			error_handler("Colors must be R,G,B inside 0/255 separated by ','");
		}
		free(full_number);
		if (i < ft_strlen(line))
			i++;
		comma_count++;
	}
	if (comma_count < 3)
	{
		free_scene_infos(scene);
		free(line);
		free(line_to_free);
		error_handler("Colors must be R,G,B inside 0/255 separated by ','");
	}
	return (sanitize_color_line(line));
}

void	import_configuration_line(char *line, t_scene *scene)
{
	int		i;
	char	*line_value;
	char	*texture;

	i = 0;
	while (line[i] && (ft_isspace(line[i])))
		i++;
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
		|| line[i] == 'E' || line[i] == 'F' || line[i] == 'C')
	{
		if (line[i] == 'F')
		{
			while (ft_isspace(line[i]))
				i++;
			line_value = ft_substr(line, i + 1, ft_strlen(line) - (i));
			if (!line_value)
			{
				free(line);
				free_scene_infos(scene);
				error_handler("Memory allocation failed");
			}
			if (scene->floor_color)
				free(scene->floor_color);
			scene->floor_color = import_color_line(scene, line_value, line);
			free(line_value);
		}
		else if (line[i] == 'C')
		{
			while (ft_isspace(line[i]))
				i++;
			line_value = ft_substr(line, i + 1, ft_strlen(line) - (i));
			if (scene->ceiling_color)
				free(scene->ceiling_color);
			scene->ceiling_color = import_color_line(scene, line_value, line);
			free(line_value);
		}
		else if (line[i] == 'N')
		{
			i++;
			if (line[i] != 'O')
			{
				free(line);
				error_handler("Textures must be NO SO WE EA following by path");
			}
			if (scene->no_texture)
				free(scene->no_texture);
			texture = sanitize_texture_line(line + i + 1);
			if (!texture)
			{
				free(line);
				free_scene_infos(scene);
				error_handler("Memory allocation failed");
			}
			if (!is_empty(texture))
					scene->no_texture = texture;
		}
		else if (line[i] == 'S')
		{
			i++;
			if (line[i] != 'O')
			{
				free(line);
				error_handler("Textures must be NO SO WE EA following by path");
			}
			if (scene->so_texture)
				free(scene->so_texture);
			texture = sanitize_texture_line(line + i + 1);
			if (!is_empty(texture))
					scene->so_texture = texture;
		}
		else if (line[i] == 'W')
		{
			i++;
			if (line[i] != 'E')
			{
				free(line);
				error_handler("Textures must be NO SO WE EA following by path");
			}
			if (scene->we_texture)
				free(scene->we_texture);
			texture = sanitize_texture_line(line + i + 1);
			if (!is_empty(texture))
					scene->we_texture = texture;
		}
		else if (line[i] == 'E')
		{
			i++;
			if (line[i] != 'A')
			{
				free(line);
				error_handler("Textures must be NO SO WE EA following by path");
			}
			if (scene->ea_texture)
				free(scene->ea_texture);
			texture = sanitize_texture_line(line + i + 1);
			if (!is_empty(texture))
				scene->ea_texture = texture;
		}
		return ;
	}
	free(line);
	free_scene_infos(scene);
	error_handler("Need configurations lines before the map");
}

void	read_scene_lines(int fd, t_scene *scene)
{
	char	*scene_line;

	(void)scene;
	scene_line = ft_strdup("debut");
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
	free(scene_line);
}
