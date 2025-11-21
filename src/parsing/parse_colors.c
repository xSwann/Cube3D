#include "../../headers/cube3D.h"

char	*clean_color_string(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	while (i < len && ft_isspace(s[i]))
		i++;
	j = len - 1;
	while (j > i && (ft_isspace(s[j]) || s[j] == '\n'))
		j--;
	if (j < i)
		return (ft_strdup(""));
	res = malloc(j - i + 2);
	if (!res)
		error_handler("Malloc failed");
	ft_memcpy(res, &s[i], j - i + 1);
	res[j - i + 1] = '\0';
	return (res);
}

static int	parse_component(char *s)
{
	int	n;

	if (!str_is_num(s))
		error_handler("Invalid RGB number");
	n = ft_atoi(s);
	if (n < 0 || n > 255)
		error_handler("RGB out of range");
	return (n);
}

int	parse_rgb(char *str)
{
	char	**split;
	int		r;
	int		g;
	int		b;
	int		color;

	split = ft_split(str, ',');
	if (!split || ft_strslen(split) != 3)
		error_handler("RGB must be R,G,B");
	r = parse_component(split[0]);
	g = parse_component(split[1]);
	b = parse_component(split[2]);
	color = (r << 16) | (g << 8) | b;
	free_tab(split);
	return (color);
}

//Retourne une ligne sanitize, si elle respecte le format imposee
char	*import_color_line( t_scene *scene, char *line, char *to_free)
{
	int		i;
	int		count;
	int		comma_count;
	char	*full_number;

	i = 0;
	count = 0;
	comma_count = 0;
	while (line[i])
	{
		full_number = find_full_number(line, &i, &count);
		if (!full_number)
			color_line_error(scene, line, to_free, "Memory allocation failed");
		if ((line[i] == ',' && comma_count == 2) || count == 0
			|| (count > 3) || (ft_atoi(full_number) > 255))
			check_rgb_error(scene, line, to_free, full_number);
		free(full_number);
		if (i < ft_strlen(line))
			i++;
		comma_count++;
	}
	if (comma_count < 3)
		color_line_error(scene, line, to_free,
			"Colors must be R,G,B inside 0/255 separated by ','");
	return (sanitize_color_line(line));
}

void	import_colors(char *line, int i, t_scene *scene)
{
	char	*line_value;
	char	current_key;

	current_key = line[i];
	if (line[i] == 'F' || line[i] == 'C')
	{
		skip_spaces(&i, line);
		line_value = ft_substr(line, i + 1, ft_strlen(line) - (i));
		if (!line_value)
		{
			free(line);
			free_scene_and_exit(scene, "Memory allocation failed");
		}
		if (current_key == 'F')
		{
			free(scene->floor_color);
			scene->floor_color = import_color_line(scene, line_value, line);
		}
		else if (current_key == 'C')
		{
			free(scene->ceiling_color);
			scene->ceiling_color = import_color_line(scene, line_value, line);
		}
		free(line_value);
	}
}
