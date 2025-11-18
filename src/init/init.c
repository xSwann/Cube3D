#include "../../headers/cube3D.h"

/* load_textures(t_app *app) : analyse et valide les données d'entrée (fichier/paramètres). */
/* échantillonne la texture au bon offset. */
void	load_textures(t_app *app)
{
	if (!app->scene.no_texture || !app->scene.so_texture ||
			!app->scene.we_texture || !app->scene.ea_texture)
		error_handler("One or more texture paths are missing");
	init_texture_img(app, &app->textures[0], app->scene.no_texture);
	if (!app->textures[0].img || !app->textures[0].addr)
		error_handler("NO texture failed to load");
	init_texture_img(app, &app->textures[1], app->scene.so_texture);
	if (!app->textures[1].img || !app->textures[1].addr)
    	error_handler("NO texture failed to load");
	init_texture_img(app, &app->textures[2], app->scene.we_texture);
	if (!app->textures[2].img || !app->textures[2].addr)
    	error_handler("NO texture failed to load");
	init_texture_img(app, &app->textures[3], app->scene.ea_texture);
	if (!app->textures[3].img || !app->textures[3].addr)
    	error_handler("NO texture failed to load");
}

/* init_player(t_app *app) : initialise les structures et valeurs nécessaires. */
void	init_player(t_app *app)
{
	app->player.pos_x = app->scene.spawn_x + 0.5;
	app->player.pos_y = app->scene.spawn_y + 0.5;
	char dir = app->scene.map_tab[app->scene.spawn_y][app->scene.spawn_x];
	if (dir == 'N')
	{
		app->player.dir_x = 0;
		app->player.dir_y = -1;
		app->player.plane_x = 0.66;
		app->player.plane_y = 0;
	}
	else if (dir == 'S')
	{
		app->player.dir_x = 0;
		app->player.dir_y = 1;
		app->player.plane_x = -0.66;
		app->player.plane_y = 0;
	}
	else if (dir == 'E')
	{
		app->player.dir_x = 1;
		app->player.dir_y = 0;
		app->player.plane_x = 0;
		app->player.plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		app->player.dir_x = -1;
		app->player.dir_y = 0;
		app->player.plane_x = 0;
		app->player.plane_y = -0.66;
	}
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
