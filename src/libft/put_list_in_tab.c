#include "../headers/libft.h"
#include "../headers/cube3D.h"

void	fill_tab(t_list *tmp_map, char **tab_map, int is_map, int i)
{
	int	line_len;
	int	j;

	line_len = 0;
	j = 0;
	while (tmp_map)
	{
		line_len = 0;
		j = 0;
		while (tmp_map->line[line_len])
			line_len++;
		tab_map[i] = malloc(sizeof(char) * line_len + 1);
		while (tmp_map->line[j])
		{
			if (is_map == 1)
				tab_map[i][j] = tmp_map->line[j];
			else if (is_map == 0)
				tab_map[i][j] = '0';
			j++;
		}
		tab_map[i][j] = '\0';
		tmp_map = tmp_map -> next;
		i++;
	}
}

char	**put_list_in_tabs(t_list *map, int is_map)
{
	t_list	*tmp_map;
	char	**tab_map;
	int		len;
	int		i;

	tmp_map = map;
	i = 0;
	len = 0;
	while (tmp_map)
	{
		tmp_map = tmp_map -> next;
		len++;
	}
	tmp_map = map;
	tab_map = malloc(sizeof(char *) * (len + 1));
	tab_map[len] = 0;
	fill_tab(tmp_map, tab_map, is_map, i);
	return (tab_map);
}