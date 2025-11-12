#include "../../headers/cube3D.h"

/* utilise la trigonométrie pour les directions/angles. */
void	movement(t_app *app)
{
	double	speed;
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	speed = 0.1;
	rot_speed = 0.05;
	if (app->keys[119])
	{
		if (app->scene.map_tab[(int)(app->player.pos_y
				+ app->player.dir_y * speed)][(int)app->player.pos_x] != '1')
			app->player.pos_y += app->player.dir_y * speed;
		if (app->scene.map_tab[(int)app->player.pos_y][(int)(app->player.pos_x
				+ app->player.dir_x * speed)] != '1')
			app->player.pos_x += app->player.dir_x * speed;
	}
	if (app->keys[115])
	{
		if (app->scene.map_tab[(int)(app->player.pos_y
				- app->player.dir_y * speed)][(int)app->player.pos_x] != '1')
			app->player.pos_y -= app->player.dir_y * speed;
		if (app->scene.map_tab[(int)app->player.pos_y][(int)(app->player.pos_x
				- app->player.dir_x * speed)] != '1')
			app->player.pos_x -= app->player.dir_x * speed;
	}
	if (app->keys[65361])
	{
		old_dir_x = app->player.dir_x;
		app->player.dir_x = app->player.dir_x * cos(rot_speed)
			- app->player.dir_y * sin(rot_speed);
		app->player.dir_y = old_dir_x * sin(rot_speed)
			+ app->player.dir_y * cos(rot_speed);
		old_plane_x = app->player.plane_x;
		app->player.plane_x = app->player.plane_x * cos(rot_speed)
			- app->player.plane_y * sin(rot_speed);
		app->player.plane_y = old_plane_x * sin(rot_speed)
			+ app->player.plane_y * cos(rot_speed);
	}
	if (app->keys[65363])
	{
		old_dir_x = app->player.dir_x;
		app->player.dir_x = app->player.dir_x * cos(-rot_speed)
			- app->player.dir_y * sin(-rot_speed);
		app->player.dir_y = old_dir_x * sin(-rot_speed)
			+ app->player.dir_y * cos(-rot_speed);
		old_plane_x = app->player.plane_x;
		app->player.plane_x = app->player.plane_x * cos(-rot_speed)
			- app->player.plane_y * sin(-rot_speed);
		app->player.plane_y = old_plane_x * sin(-rot_speed)
			+ app->player.plane_y * cos(-rot_speed);
	}
}
