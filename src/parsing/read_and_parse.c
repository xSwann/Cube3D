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
    char **raw_map;

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

char	*clean_color_string(char *s)
{
	int	i;
	int	j;
	int	len;
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

t_scene parse_file(char *file_name)
{
    t_scene scene;

	scene = create_scene(file_name);
	find_spawn(&scene);
    validate_textures(&scene);
    validate_map(scene.map_tab, scene.map_width, scene.map_height);
    return (scene);
}
