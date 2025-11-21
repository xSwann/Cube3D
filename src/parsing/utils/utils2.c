#include "../../../headers/cube3D.h"

void	skip_spaces(int *i, char *line)
{
	while (ft_isspace(line[*i]))
		(*i)++;
}

void	copy_chars(int *i, int *j, char **copy_tab, char **tab)
{
	while (*j < ft_strlen(tab[*i]))
	{
		copy_tab[*i][*j] = tab[*i][*j];
		(*j)++;
	}
}

char	*find_full_number(char *line, int *i, int *count)
{
	int		start;
	int		end;
	char	*full_number;

	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	start = *i;
	*count = 0;
	while (line[*i] && ft_isdigit(line[*i]))
	{
		(*i)++;
		(*count)++;
	}
	end = *i;
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	full_number = ft_substr(line, start, end - start);
	return (full_number);
}
