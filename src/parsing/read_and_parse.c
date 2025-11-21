/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:15:19 by slatrech          #+#    #+#             */
/*   Updated: 2025/11/21 16:15:20 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cube3D.h"

void	init_scene(t_scene *scene)
{
	scene->ceiling_color = NULL;
	scene->floor_color = NULL;
	scene->ea_texture = NULL;
	scene->so_texture = NULL;
	scene->no_texture = NULL;
	scene->we_texture = NULL;
	scene->map_struct = NULL;
	scene->map_tab = NULL;
}

t_scene	create_scene(char *scene_name)
{
	t_scene		scene;
	int			fd;
	char		**raw_map;

	fd = open(scene_name, O_RDONLY);
	if (fd < 0)
		error_handler("File does not exist");
	init_scene(&scene);
	read_scene_lines(fd, &scene);
	raw_map = put_list_in_tabs(scene.map_struct, 1);
	get_width_and_height(raw_map, &scene);
	scene.map_tab = uniform_map(raw_map, scene.map_width, scene.map_height);
	free_tab(raw_map);
	find_spawn(&scene);
	close(fd);
	return (scene);
}

t_scene	parse_file(char *file_name)
{
	t_scene	scene;

	scene = create_scene(file_name);
	check_border(&scene);
	validate_textures(&scene);
	return (scene);
}
