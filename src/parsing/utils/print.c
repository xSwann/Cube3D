/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:15:53 by slatrech          #+#    #+#             */
/*   Updated: 2025/11/21 16:15:54 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cube3D.h"

void	print_scene(t_scene *scene)
{	
	print_scene_infos(scene);
	print_tab(scene->map_tab);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	print_list(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	printf("%s\n", tmp -> line);
	while (tmp -> next)
	{
		tmp = tmp -> next;
		printf("%s\n", tmp -> line);
	}
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
