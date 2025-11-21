/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:51:15 by elanteno          #+#    #+#             */
/*   Updated: 2025/11/20 16:55:14 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cube3D.h"

void	free_scene(t_scene *scene)
{
    free_scene_infos(scene);
    free_map(scene->map_struct);
	if (scene->map_tab)
		free_tab(scene->map_tab);
}

void	free_int_tab(int **tab, int height)
{
	int i;

	i = 0;
	while(i < height)
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_map(t_list *map)
{
	t_list	*current;
	t_list	*next;

	current = map;
	while (current)
	{
		next = current->next;
		if (current->line)
			free(current->line);
		free(current);
		current = next;
	}
}

void	free_scene_and_exit(t_scene *scene, char *msg)
{
	free_scene(scene);
	error_handler(msg);
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

void	free_image(t_app *app)
{
	if (app->frame.img)
		mlx_destroy_image(app->mlx, app->frame.img);
}

void	free_all_data(t_app *app)
{
	if (!app)
		return ;
	free_textures(app);
	free_image(app);
	free_scene(&app->scene);
}
