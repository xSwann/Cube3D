#include "../../headers/cube3D.h"

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

int	is_line_valid(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
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