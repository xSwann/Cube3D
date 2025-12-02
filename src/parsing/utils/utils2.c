/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:15:59 by slatrech          #+#    #+#             */
/*   Updated: 2025/12/02 10:53:34 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	str_is_rgb_line(char *nb, t_scene *scene, char *line, char *to_free)
{
	int	i;

	i = 0;
	while (nb[i])
	{
		if (!ft_isdigit(nb[i]) && nb[i] != ','
			&& !ft_isspace(nb[i]))
			color_line_error(scene, line, to_free);
		i++;
	}
}
