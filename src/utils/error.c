/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanteno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:42:11 by elanteno          #+#    #+#             */
/*   Updated: 2025/11/06 12:39:35 by elanteno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	super_exit(t_data *data, int code)
{
	if (!data)
		exit(code);
	if (data->win && data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		mlx_loop_end(data->mlx);
		free(data->mlx);
	}
	free_all_data(data);
	exit(code);
}

int	quit_game(t_data *data)
{
	super_exit(data, 0);
	return (0);
}

