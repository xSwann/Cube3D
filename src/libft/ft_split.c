/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:42:47 by slatrech          #+#    #+#             */
/*   Updated: 2025/11/17 06:51:10 by elanteno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"
static size_t ft_countwords(const char *str, int c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((i == 0 || str[i - 1] == c) && str[i] != c)
			j++;
		i++;
	}
	return (j);
}

static size_t ft_wordlen(const char *str, int c, size_t k)
{
	size_t	j;

	j = 0;
	while (str[k] && str[k] == c)
		k++;
	while (str[k + j] && str[k + j] != c)
		j++;
	return (j);
}

static void ft_free_table(char **table)
{
	size_t	i;

	i = 0;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}

static char **ft_build_table(const char *s, char c, char **table, size_t count)
{
	size_t j;
	size_t k;
	size_t len;

	j = 0;
	k = 0;
	while (j < count)
	{
		len = ft_wordlen(s, c, k);
		table[j] = ft_calloc(len + 1, sizeof(char));
		if (!table[j])
		{
			ft_free_table(table);
			return (NULL);
		}
		while (s[k] && s[k] == c)
			k++;
		ft_memcpy(table[j], s + k, len);
		table[j][len] = '\0';
		k += len;
		j++;
	}
	table[j] = NULL;
	return (table);
}

char **ft_split(const char *s, char c)
{
	char	**table;
	size_t	count;

	if (!s)
		return (NULL);
	count = ft_countwords(s, c);
	table = ft_calloc(count + 1, sizeof(char *));
	if (!table)
		return (NULL);
	return ft_build_table(s, c, table, count);
}
