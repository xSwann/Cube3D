/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:16:11 by slatrech          #+#    #+#             */
/*   Updated: 2025/11/21 16:16:12 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cube3D.h"

void	load_textures(t_app *app)
{
	if (!app->scene.no_texture || !app->scene.so_texture
		|| !app->scene.we_texture || !app->scene.ea_texture)
		error_handler("One or more texture paths are missing");
	init_texture_img(app, &app->textures[0], app->scene.no_texture);
	if (!app->textures[0].img || !app->textures[0].addr)
		error_handler("NO texture failed to load");
	init_texture_img(app, &app->textures[1], app->scene.so_texture);
	if (!app->textures[1].img || !app->textures[1].addr)
		error_handler("SO texture failed to load");
	init_texture_img(app, &app->textures[2], app->scene.we_texture);
	if (!app->textures[2].img || !app->textures[2].addr)
		error_handler("WE texture failed to load");
	init_texture_img(app, &app->textures[3], app->scene.ea_texture);
	if (!app->textures[3].img || !app->textures[3].addr)
		error_handler("EA texture failed to load");
}

void	init_player(t_app *app)
{
	char	dir;

	app->player.pos_x = app->scene.spawn_x + 0.5;
	app->player.pos_y = app->scene.spawn_y + 0.5;
	dir = app->scene.map_tab[app->scene.spawn_y][app->scene.spawn_x];
	init_player_dir(app, dir);
	app->scene.map_tab[app->scene.spawn_y][app->scene.spawn_x] = '0';
}

int	key_press(int key, t_app *app)
{
	if (key >= 0 && key < 65536)
		app->keys[key] = 1;
	return (0);
}

int	key_release(int key, t_app *app)
{
	if (key >= 0 && key < 65536)
		app->keys[key] = 0;
	return (0);
}
