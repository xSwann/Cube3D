#include "../../headers/cube3D.h"

void	error_handler(char *error_message)
{
	printf("Error:\n%s", error_message);
	exit(EXIT_FAILURE);
}

int is_empty(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}
//Enleve le \n a la fin de la ligne (get_next_line renvoie des lignes avec un \n)
char *remove_endl(char *str)
{
	int i;
	char *str_without_endl;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		i++;
	}
	str_without_endl = ft_substr(str, 0, i);
	free(str);
	return (str_without_endl);
}

//Les color lines ont ressortent sous le format "255,255,255" peut importe si l'user entre des expaces avant, apres ou entre les nombres et les virgules
char *sanitize_color_line(char *line)
{
	int i;
	char *str;
	int start;
	char *sub;
	char *new_str;

	i = 0;
	start = 0;
	str = NULL;
	while (line[i])
	{
		while(line[i] && ft_isspace(line[i]))
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
char *sanitize_texture_line(char *line)
{
	int i;
	char *str;
	int start;
	char *sub;
	int end;

	i = 0;
	start = 0;
	end = ft_strlen(line) - 1;
	str = NULL;
	while(line[i] && ft_isspace(line[i]))
		i++;
	while(ft_isspace(line[end]))
		end--;
	while (line[i] && i < end)
	{
		start = i;
		while (line[i] && i < end)
			i++;
		sub = ft_substr(line, start, end - start);
		str = ft_strjoin(str, sub);
		free(sub);
	}
	return (str);
}

//Retourne une ligne sanitize, si elle respecte le formattage imposee
char *import_color_line( t_scene *scene, char *line)
{
	int i;
	int first_number;
	int last_number;
	int count;
	int coma_count;
	char *full_number;

	i = 0;
	count = 0;
	first_number = 0;
	coma_count = 0;
	last_number = 0;
	while(line[i])
	{
		while(line[i] && ft_isspace(line[i]))
			i++;
		first_number = i;
		count = 0;
		while(line[i] && ft_isdigit(line[i]))
		{
			i++;
			count++;
		}
		last_number = i;
		while(line[i] && ft_isspace(line[i]))
			i++;
		full_number = ft_substr(line, first_number, last_number);
		if(count == 0 || (line[i] != ',' && coma_count != 2) || (count > 3) || (ft_atoi(full_number) > 255))
		{
			free_scene(scene);
			free(full_number);
			free(line);
			error_handler("Floor and Ceilling color must be R,G,B inside 0 and 255 separated by ','");
		}
		free(full_number);
		if (i < ft_strlen(line))
			i++;
		coma_count++;
	}
	return (sanitize_color_line(line));
}


//Importe les differentes lignes de configuration dans la structure en verifiant que leur denominateurs soient bien formatee
void	import_configuration_line(char *line, t_scene *scene)
{
	int i;
	char *line_value;

	i = 0;
	while(line[i] && (ft_isspace(line[i])))
		i++;
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E' || line[i] == 'F' || line[i] == 'C')
	{
		if(line[i] == 'F')
		{
			//i++;
			while(ft_isspace(line[i]))
				i++;
			line_value = ft_substr(line, i + 1, ft_strlen(line) - (i));
			//free(line);
			scene->floor_color = import_color_line(scene, line_value);
			free(line_value);
		}
		else if(line[i] == 'C')
		{
			//i++;
			while(ft_isspace(line[i]))
				i++;
			line_value = ft_substr(line, i + 1, ft_strlen(line) - (i));
			//free(line);
			scene->ceiling_color = import_color_line(scene, line_value);
			free(line_value);
		}
		else if(line[i] == 'N')
		{
			i++;
			if (line[i] != 'O')
				error_handler("A: Textures path must be NO SO WE EA following by the path");
			scene->no_texture = sanitize_texture_line(line + i + 1);
		}
		else if(line[i] == 'S')
		{
			i++;
			if (line[i] != 'O')
				error_handler("B: Textures path must be NO SO WE EA following by the path");
			scene->so_texture = sanitize_texture_line(line + i + 1);
		}
		else if(line[i] == 'W')
		{
			i++;
			if (line[i] != 'E')
				error_handler("C: Textures path must be NO SO WE EA following by the path");
			scene->we_texture = sanitize_texture_line(line + i + 1);
		}
		else if(line[i] == 'E')
		{
			i++;
			if (line[i] != 'A')
				error_handler("D: Textures path must be NO SO WE EA following by the path");
			while(ft_isspace(line[i]))
				i++;
			scene->ea_texture = sanitize_texture_line(line + 2);
		}
		return ;
	}
	error_handler("Need configurations lines before the map\n");
}

//Fais des appels a get_next_line pour lire le fichier .cub jusqu'a que tout les champs de configuration soit remplis ou qu'une erreur soit trouvee
void	read_scene_lines(int fd, t_scene *scene)
{
	char	*scene_line;

	(void)scene;
	scene_line = "debut";
	while (scene_line && (is_empty(scene->ceiling_color) || is_empty(scene->floor_color) 
	|| is_empty(scene->no_texture) || is_empty(scene->so_texture) || is_empty(scene->we_texture)
	|| is_empty(scene->ea_texture)))
	{
		scene_line = remove_endl(get_next_line(fd));
		if (scene_line && scene_line[0] != '\n')
		{
			import_configuration_line(scene_line, scene);
			//printf("line: %s", scene_line);
		}
		free(scene_line);
	}
}
void init_scene(t_scene *scene)
{
	scene->ceiling_color = NULL;
	scene->floor_color = NULL;
	scene->ea_texture = NULL;
	scene->so_texture = NULL;
	scene->no_texture = NULL;
	scene->we_texture = NULL;
}

void free_scene(t_scene *scene)
{
	if(scene->ceiling_color)
		free(scene->ceiling_color);
	if(scene->floor_color)
		free(scene->floor_color);
	if(scene->ea_texture)
		free(scene->ea_texture);
	if(scene->so_texture)
		free(scene->so_texture);
	if(scene->no_texture)
		free(scene->no_texture);
	if(scene->we_texture)
		free(scene->we_texture);
}

t_scene	read_scene(char *scene_name)
{
	int		fd;
	t_scene	scene;

	fd = open(scene_name, O_RDONLY);
	if (fd < 0)
	{
		printf("File does not exit");
		exit(EXIT_FAILURE);
	}
	init_scene(&scene);
	read_scene_lines(fd, &scene);
	return (scene);
}

t_scene parse_file(char *file_name)
{
    t_scene scene;

	scene = read_scene(file_name);
	printf("floor: %s\n", scene.floor_color);
	printf("ceilling: %s\n", scene.ceiling_color);
	printf("no: %s\n", scene.no_texture);
	printf("so: %s\n", scene.so_texture);
	printf("we: %s\n", scene.we_texture);
	printf("ea: %s\n", scene.ea_texture);
    return (scene);
}

