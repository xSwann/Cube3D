/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:42:45 by slatrech          #+#    #+#             */
/*   Updated: 2025/11/05 10:58:42 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

void	*ft_memset(void *p, int value, size_t count)
{
	unsigned char	*char_p;
	size_t			i;

	i = 0;
	char_p = (unsigned char *)p;
	while (i < count)
	{
		char_p[i] = (unsigned char)value;
		i++;
	}
	return (p);
}
