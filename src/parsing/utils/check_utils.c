/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:15:47 by slatrech          #+#    #+#             */
/*   Updated: 2025/11/21 16:15:48 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/cube3D.h"

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

void	is_map_name_valid(char *map_name)
{
	int	len;

	len = ft_strlen(map_name);
	if (len <= 4 || map_name[len -4] != '.' || map_name[len -3] != 'c'
		|| map_name[len -2] != 'u' || map_name[len -1] != 'b'
		|| map_name[len] != '\0')
		error_handler("Map should be a .cub file");
}

int	is_open_tile(char tile)
{
	if (tile == '0' || tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
		return (1);
	return (0);
}

int	is_spawn_tile(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_empty(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}
