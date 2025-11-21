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

void	color_line_error(t_scene *scene, char *line, char *to_free, char *msg)
{
	free_scene_infos(scene);
	free(line);
	free(to_free);
	error_handler(msg);
}

void	check_rgb_error(t_scene *scene, char *line, char *to_free, char *nb)
{
	free(nb);
	color_line_error(scene, line, to_free,
		"Colors must be R,G,B inside 0/255 separated by ','");
}
