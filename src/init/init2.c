/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanteno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 08:04:28 by elanteno          #+#    #+#             */
/*   Updated: 2025/11/20 08:06:23 by elanteno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cube3D.h"

static void	init_player_dir_ns(t_app *app, char dir)
{
	app->player.dir_x = 0;
	app->player.plane_y = 0;
	if (dir == 'N')
	{
		app->player.dir_y = -1;
		app->player.plane_x = 0.66;
	}
	else
	{
		app->player.dir_y = 1;
		app->player.plane_x = -0.66;
	}
}

static void	init_player_dir_ew(t_app *app, char dir)
{
	app->player.dir_y = 0;
	app->player.plane_x = 0;
	if (dir == 'E')
	{
		app->player.dir_x = 1;
		app->player.plane_y = 0.66;
	}
	else
	{
		app->player.dir_x = -1;
		app->player.plane_y = -0.66;
	}
}

void	init_player_dir(t_app *app, char dir)
{
	if (dir == 'N' || dir == 'S')
		init_player_dir_ns(app, dir);
	else if (dir == 'E' || dir == 'W')
		init_player_dir_ew(app, dir);
}
