
#include "../../headers/cube3D.h"

void	is_map_name_valid(char *map_name)
{
	int	len;

	len = ft_strlen(map_name);
	if (len <= 4 || map_name[len -4] != '.' || map_name[len -3] != 'c'
		|| map_name[len -2] != 'u' || map_name[len -1] != 'b'
		|| map_name[len] != '\0')
		error_handler("Map should be a .cub file");
}

void get_width_and_height(char **raw_map, t_scene *scene)
{
    int height;
    int width;
    int old_width;

    height = 0;
    width = 0;

    while(raw_map[height])
    {
        old_width = 0;
        while (raw_map[height][old_width])
            old_width++;
        if (old_width > width)
            width = old_width;
        height++;
    }
    scene->map_width = width;
    scene->map_height = height;
}
//Uniform the map, all lines are the same len and void are replaced by ' '
char **uniform_map(char **map, int width, int height)
{
    char **square_map;
    int i;
    int j;

    i = 0;
    j = 0;
    square_map = malloc(sizeof(char *) * (height + 1));
    if (!square_map)
        error_handler("Memory allocation failed");
    square_map[height] = 0;
    while (i < height)
    {
        j = 0;
        square_map[i] = malloc(sizeof(char) * (width + 1));
        if (!square_map[i])
            error_handler("Memory allocation failed");
        square_map[i][width] = '\0';
        while(j < ft_strlen(map[i]))
        {
            square_map[i][j] = map[i][j]; 
            j++;
        }
        while(j < width)
        {
            square_map[i][j] = ' ';
            j++;
        }
        i++;
    }
    return (square_map);
}

int is_open_tile(char tile)
{
    if (tile == '0' || tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
        return (1);
    return (0);
}


static int	is_spawn_tile(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	find_spawn(t_scene *scene)
{
	int	y;
	int	x;
	int	found;

	found = 0;
	y = 0;
	while (y < scene->map_height)
	{
		x = 0;
		while (x < scene->map_width)
		{
			if (is_spawn_tile(scene->map_tab[y][x]))
			{
				scene->spawn_x = x;
				scene->spawn_y = y;
				scene->spawn_orientation = scene->map_tab[y][x];
				found++;
			}
			x++;
		}
		y++;
	}
	if (found != 1)
		free_scene_and_exit(scene, "Map must contain exactly one player spawn");
}

void    check_direct_border(t_scene *scene)
{
    int i;
    int j;

    j = 0;
    while (j < scene->map_width)
    {
        if (is_open_tile(scene->map_tab[0][j]))
            free_scene_and_exit(scene, "Map open on top border");
        j++;
    }
    j = 0;
    while (j < scene->map_width)
    {
        if (is_open_tile(scene->map_tab[scene->map_height - 1][j]))
            free_scene_and_exit(scene, "Map open on bottom border");
        j++;
    }
    i = 0;
    while (i < scene->map_height)
    {
        if (is_open_tile(scene->map_tab[i][0]))
            free_scene_and_exit(scene, "Map open on left border");
        i++;
    }
    i = 0;
    while (i < scene->map_height)
    {
        if (is_open_tile(scene->map_tab[i][scene->map_width - 1]))
            free_scene_and_exit(scene, "Map open on right border");
        i++;
    }
}

void    check_border(t_scene *scene)
{
    int     **visited;
    int     i;
    int     j;
    t_fill  f;

    check_direct_border(scene);

    visited = malloc(sizeof(int *) * scene->map_height);
    if (!visited)
        free_scene_and_exit(scene, "Memory allocation failed");
    i = 0;
    while (i < scene->map_height)
    {
        visited[i] = malloc(sizeof(int) * scene->map_width);
        if (!visited[i])
            free_scene_and_exit(scene, "Memory allocation failed");

        j = 0;
        while (j < scene->map_width)
        {
            visited[i][j] = 0;
            j++;
        }
        i++;
    }
    f.map = scene->map_tab;
    f.visited = visited;
    f.width = scene->map_width;
    f.height = scene->map_height;
    j = 0;
    while (j < scene->map_width)
    {
        if (scene->map_tab[0][j] == ' ')
            flood(scene, &f, j, 0);
        j++;
    }
    j = 0;
    while (j < scene->map_width)
    {
        if (scene->map_tab[scene->map_height - 1][j] == ' ')
            flood(scene, &f, j, scene->map_height - 1);
        j++;
    }
    i = 0;
    while (i < scene->map_height)
    {
        if (scene->map_tab[i][0] == ' ')
            flood(scene, &f, 0, i);
        i++;
    }
    i = 0;
    while (i < scene->map_height)
    {
        if (scene->map_tab[i][scene->map_width - 1] == ' ')
            flood(scene, &f, scene->map_width - 1, i);
        i++;
    }
    j = 0;
    i = 0;
    free_int_tab(visited, scene->map_height);
}





