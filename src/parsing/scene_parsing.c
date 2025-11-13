#include "../../headers/cube3D.h"


void	print_scene(t_scene *scene)
{	
	print_scene_infos(scene);
	print_list(scene->map_struct);
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
void	fill_tab(t_list *tmp_map, char **tab_map, int is_map, int i)
{
	int	line_len;
	int	j;

	line_len = 0;
	j = 0;
	while (tmp_map)
	{
		line_len = 0;
		j = 0;
		while (tmp_map->line[line_len])
			line_len++;
		tab_map[i] = malloc(sizeof(char) * line_len + 1);
		while (tmp_map->line[j])
		{
			if (is_map == 1)
				tab_map[i][j] = tmp_map->line[j];
			else if (is_map == 0)
				tab_map[i][j] = '0';
			j++;
		}
		tab_map[i][j] = '\0';
		tmp_map = tmp_map -> next;
		i++;
	}
}

char	**put_list_in_tabs(t_list *map, int is_map)
{
	t_list	*tmp_map;
	char	**tab_map;
	int		len;
	int		i;

	tmp_map = map;
	i = 0;
	len = 0;
	while (tmp_map)
	{
		tmp_map = tmp_map -> next;
		len++;
	}
	tmp_map = map;
	tab_map = malloc(sizeof(char *) * (len + 1));
	tab_map[len] = 0;
	fill_tab(tmp_map, tab_map, is_map, i);
	return (tab_map);
}

void	print_scene_infos(t_scene *scene)
{
	printf("floor: %s\n", scene->floor_color);
	printf("ceilling: %s\n", scene->ceiling_color);
	printf("no: %s\n", scene->no_texture);
	printf("so: %s\n", scene->so_texture);
	printf("we: %s\n", scene->we_texture);
	printf("ea: %s\n", scene->ea_texture);
}

void	free_scene(t_scene *scene)
{
    free_scene_infos(scene);
    free_map(scene->map_struct);
	free_tab(scene->map_tab);
}

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
void remove_endl(char **str)
{
    int i;
    char *str_without_endl;

    if (!str || !*str)
        return;

    i = 0;
    if ((*str)[i] == '\n')
    {
        free(*str);
        *str = ft_strdup("");
        return;
    }
    while ((*str)[i] && (*str)[i] != '\n')
        i++;

    str_without_endl = ft_substr(*str, 0, i);
    free(*str);
    *str = str_without_endl;
}

//Les color lines ressortent sous le format "255,255,255" peut importe si l'user entre des espaces avant, apres ou entre les nombres et les virgules
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
	end = ft_strlen(line) -1;
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
		sub = ft_substr(line, start, end + 1 - start);
		str = ft_strjoin(str, sub);
		free(sub);
	}
	return (str);
}

//Retourne une ligne sanitize, si elle respecte le format imposee
char *import_color_line( t_scene *scene, char *line, char *line_to_free)
{
	int i;
	int first_number;
	int last_number;
	int count;
	int comma_count;
	char *full_number;

	i = 0;
	count = 0;
	first_number = 0;
	comma_count = 0;
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
		full_number = ft_substr(line, first_number, last_number - first_number);
		if (!full_number)
		{
			free_scene_infos(scene);
			free(line);
			free(line_to_free);
			error_handler("Memory allocation failed");
		}
		if((line[i] == ',' && comma_count == 2) || count == 0 || (line[i] != ',' && comma_count != 2) || (count > 3) || (ft_atoi(full_number) > 255))
		{
			free_scene_infos(scene);
			free(full_number);
			free(line);
			free(line_to_free);
			error_handler("Floor and Ceilling color must be R,G,B inside 0 and 255 separated by ','");
		}
		free(full_number);
		if (i < ft_strlen(line))
			i++;
		comma_count++;
	}
	return (sanitize_color_line(line));
}

int have_good_extension(char *texture)
{
	int	len;

	len = ft_strlen(texture);
	if (len <= 4 || texture[len -4] != '.' || texture[len -3] != 'x'
		|| texture[len -2] != 'p' || texture[len -1] != 'm'
		|| texture[len] != '\0')
		return (0);
	return (1);
}


//Importe les differentes lignes de configuration dans la structure en verifiant que leur denominateurs soient bien formatee
//Les lignes peuvent etre ecrites avec ou sans un ou plusieurs espaces
//Ex: "NO ./no_texture.xp" et "NO./no_texture.xp" sont des lignes de textures valides
//"NORTH ./no_texture.xp" est aussi une ligne valide, le fichier "RTH ./no_texture.xp" va essayer d'etre ouvert
//NO ./north.xpm F 220,100,0.xpm est une ligne valide car un fichier peut s'appeller "./north.xpm F 220,100,0.xpm"
//Les doublons sont accepte, la derniere valeur sera prise en compte
void	import_configuration_line(char *line, t_scene *scene)
{
	int i;
	char *line_value;
	char *texture;

	i = 0;
	while(line[i] && (ft_isspace(line[i])))
		i++;
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E' || line[i] == 'F' || line[i] == 'C')
	{
		if(line[i] == 'F')
		{
			while(ft_isspace(line[i]))
				i++;
			line_value = ft_substr(line, i + 1, ft_strlen(line) - (i));
			if (!line_value)  // Si substr échoue
			{
				free(line);
				free_scene_infos(scene);
				error_handler("Memory allocation failed");
			}
			if(scene->floor_color)
				free(scene->floor_color);
			scene->floor_color = import_color_line(scene, line_value, line);
			free(line_value);
		}
		else if(line[i] == 'C')
		{
			while(ft_isspace(line[i]))
				i++;
			line_value = ft_substr(line, i + 1, ft_strlen(line) - (i));
			if(scene->ceiling_color)
				free(scene->ceiling_color);
			scene->ceiling_color = import_color_line(scene, line_value, line);
			free(line_value);
		}
		else if(line[i] == 'N')
		{
			i++;
			if (line[i] != 'O')
			{
				free(line);
				error_handler("A: Textures path must be NO SO WE EA following by the path");
			}
			if(scene->no_texture)
				free(scene->no_texture);
			texture = sanitize_texture_line(line + i + 1);
			if (!texture)  // Si sanitize échoue (car il peut retourner NULL maintenant)
			{
				free(line);
				free_scene_infos(scene);
				error_handler("Memory allocation failed");
			}
			if (!is_empty(texture))
			{
				if (have_good_extension(texture))
					scene->no_texture = texture;
				else
				{
					free(texture);
					free(line);
					free_scene_infos(scene);
					error_handler("Textures should be .xpm files");
				}
			}
		}
		else if(line[i] == 'S')
		{
			i++;
			if (line[i] != 'O')
			{
				free(line);
				error_handler("B: Textures path must be NO SO WE EA following by the path");
			}
			if(scene->so_texture)
				free(scene->so_texture);
			texture = sanitize_texture_line(line + i + 1);
			if (!is_empty(texture))
			{
				if (have_good_extension(texture))
					scene->so_texture = texture;
				else
				{
					free(texture);
					free(line);
					free_scene_infos(scene);
					error_handler("Textures should be .xpm files");
				}
			}
		}
		else if(line[i] == 'W')
		{
			i++;
			if (line[i] != 'E')
			{
				free(line);
				error_handler("C: Textures path must be NO SO WE EA following by the path");
			}
			if(scene->we_texture)
				free(scene->we_texture);
			texture = sanitize_texture_line(line + i + 1);
			if (!is_empty(texture))
			{
				if (have_good_extension(texture))
					scene->we_texture = texture;
				else
				{
					free(texture);
					free(line);
					free_scene_infos(scene);
					error_handler("Textures should be .xpm files");
				}
			}
		}
		else if(line[i] == 'E')
		{
			i++;
			if (line[i] != 'A')
			{
				free(line);
				error_handler("D: Textures path must be NO SO WE EA following by the path");
			}
			if(scene->ea_texture)
				free(scene->ea_texture);
			texture = sanitize_texture_line(line + i + 1);
			if (!is_empty(texture))
			{
				if (have_good_extension(texture))
				scene->ea_texture = texture;
				else
				{
					free(texture);
					free(line);
					free_scene_infos(scene);
					error_handler("Textures should be .xpm files");
				}
			}
		}
		return ;
	}
	free(line);
	free_scene_infos(scene);
	error_handler("Need configurations lines before the map\n");
}

int is_configuration_full(t_scene *scene)
{
	if(is_empty(scene->ceiling_color) || is_empty(scene->floor_color) 
	|| is_empty(scene->no_texture) || is_empty(scene->so_texture) || is_empty(scene->we_texture)
	|| is_empty(scene->ea_texture))
		return (0);
	return(1);
}

//Fais des appels a get_next_line pour lire le fichier .cub jusqu'a que tout les champs de configuration soit remplis ou qu'une erreur soit trouvee
void	read_scene_lines(int fd, t_scene *scene)
{
	char	*scene_line;

	(void)scene;
	scene_line = ft_strdup("debut");

		while (!is_configuration_full(scene))
		{
			free(scene_line);
			scene_line = get_next_line(fd);
			remove_endl(&scene_line);
			if (!scene_line)
				return ;
			if (scene_line && scene_line[0] != '\n')
				import_configuration_line(scene_line, scene);
		}
		free(scene_line);
		scene_line = get_next_line(fd);
		remove_endl(&scene_line);
		while(scene_line && is_empty(scene_line))
		{
			free(scene_line);
			scene_line = get_next_line(fd);
			remove_endl(&scene_line);
			if (!scene_line)
				error_handler("You should enter a map");

		} 
		while (scene_line && !is_empty(scene_line))
		{
			put_map_in_list(scene_line, &scene->map_struct);
			free(scene_line);
			scene_line = get_next_line(fd);
			remove_endl(&scene_line);
		}
		if (!scene->map_struct->line)
			error_handler("You should enter a map");
	free(scene_line);
}
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

void free_scene_infos(t_scene *scene)
{
	free(scene->ceiling_color);
	free(scene->floor_color);
	free(scene->ea_texture);
	free(scene->so_texture);
	free(scene->no_texture);
	free(scene->we_texture);
}

t_scene	read_scene(char *scene_name)
{
	int		fd;
	t_scene	scene;
	int i;

	i = 0;
	fd = open(scene_name, O_RDONLY);
	if (fd < 0)
	{
		printf("File does not exit");
		exit(EXIT_FAILURE);
	}
	init_scene(&scene);
	read_scene_lines(fd, &scene);
	scene.map_tab = put_list_in_tabs(scene.map_struct, 1);
	return (scene);
}

t_scene parse_file(char *file_name)
{
    t_scene scene;

	scene = read_scene(file_name);
    return (scene);
}

