/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:15:56 by slatrech          #+#    #+#             */
/*   Updated: 2025/11/21 16:15:57 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cube3D.h"

int	list_size(t_list *list)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = list;
	while (tmp)
	{
		tmp = tmp -> next;
		i++;
	}
	return (i);
}

void	add_back(t_list **list, t_list *new_node)
{
	t_list	*tmp;

	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	tmp = *list;
	while (tmp -> next)
		tmp = tmp -> next;
	tmp -> next = new_node;
}

t_list	*create_node(char *line)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->line = ft_strdup(line);
	if (!new_node->line)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

int	put_map_in_list(char *map_line, t_scene *scene)
{
	t_list	*node;

	if (map_line)
	{
		if (is_line_valid(map_line))
		{
			node = create_node(map_line);
			add_back(&scene->map_struct, node);
		}
		else
		{
			free_scene(scene);
			free(map_line);
			error_handler("Non-valid map");
		}
	}
	return (0);
}

void	remove_endl(char **str)
{
	int		i;
	char	*str_without_endl;

	if (!str || !*str)
		return ;
	i = 0;
	if ((*str)[i] == '\n')
	{
		free(*str);
		*str = ft_strdup("");
		return ;
	}
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	str_without_endl = ft_substr(*str, 0, i);
	free(*str);
	*str = str_without_endl;
}
