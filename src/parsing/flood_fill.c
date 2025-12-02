/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:15:02 by slatrech          #+#    #+#             */
/*   Updated: 2025/12/02 10:50:04 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cube3D.h"

void	flood(t_scene *scene, t_fill *f, int x, int y)
{
	char	tile;

	if (x < 0 || y < 0 || x >= f->width || y >= f->height)
		return ;
	if (f->visited[y][x] == 1)
		return ;
	tile = f->map[y][x];
	if (tile == '1')
		return ;
	if (is_open_tile(tile))
	{
		free_int_tab(f->visited, f->height);
		free_scene_and_exit(scene, "Map is not closed by walls");
	}
	f->visited[y][x] = 1;
	flood(scene, f, x + 1, y);
	flood(scene, f, x - 1, y);
	flood(scene, f, x, y + 1);
	flood(scene, f, x, y - 1);
}

int	**alloc_visited(t_scene *scene)
{
	int		**visited;
	int		i;
	int		j;

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
	return (visited);
}

void	init_fill_struct(t_fill *f, t_scene *scene, int **visited)
{
	f->map = scene->map_tab;
	f->visited = visited;
	f->width = scene->map_width;
	f->height = scene->map_height;
}

void	flood_top_and_bottom(int *j, t_scene *scene, t_fill *f)
{
	while (*j < scene->map_width)
	{
		if (scene->map_tab[0][*j] == ' ')
			flood(scene, f, *j, 0);
		(*j)++;
	}
	*j = 0;
	while (*j < scene->map_width)
	{
		if (scene->map_tab[scene->map_height - 1][*j] == ' ')
			flood(scene, f, *j, scene->map_height - 1);
		(*j)++;
	}
}

void	border_flood_calls(t_scene *scene, t_fill *f)
{
	int	i;
	int	j;

	j = 0;
	flood_top_and_bottom(&j, scene, f);
	i = 0;
	while (i < scene->map_height)
	{
		if (scene->map_tab[i][0] == ' ')
			flood(scene, f, 0, i);
		i++;
	}
	i = 0;
	while (i < scene->map_height)
	{
		if (scene->map_tab[i][scene->map_width - 1] == ' ')
			flood(scene, f, scene->map_width - 1, i);
		i++;
	}
}
