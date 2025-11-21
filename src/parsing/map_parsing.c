/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:15:08 by slatrech          #+#    #+#             */
/*   Updated: 2025/11/21 16:15:09 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cube3D.h"

void	get_width_and_height(char **raw_map, t_scene *scene)
{
	int	height;
	int	width;
	int	old_width;

	height = 0;
	width = 0;
	while (raw_map[height])
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
char	**uniform_map(char **map, int width, int height)
{
	char	**square_map;
	int		i;
	int		j;

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
		copy_chars(&i, &j, square_map, map);
		while (j < width)
			square_map[i][j++] = ' ';
		i++;
	}
	return (square_map);
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

void	check_direct_border(t_scene *scene)
{
	int	i;
	int	j;

	j = 0;
	while (j < scene->map_width)
		if (is_open_tile(scene->map_tab[0][j++]))
			free_scene_and_exit(scene, "Map open on top border");
	j = 0;
	while (j < scene->map_width)
		if (is_open_tile(scene->map_tab[scene->map_height - 1][j++]))
			free_scene_and_exit(scene, "Map open on bottom border");
	i = 0;
	while (i < scene->map_height)
		if (is_open_tile(scene->map_tab[i++][0]))
			free_scene_and_exit(scene, "Map open on left border");
	i = 0;
	while (i < scene->map_height)
		if (is_open_tile(scene->map_tab[i++][scene->map_width - 1]))
			free_scene_and_exit(scene, "Map open on right border");
}

void	check_border(t_scene *scene)
{
	int		**visited;
	t_fill	f;

	check_direct_border(scene);
	visited = alloc_visited(scene);
	init_fill_struct(&f, scene, visited);
	border_flood_calls(scene, &f);
	free_int_tab(visited, scene->map_height);
}
