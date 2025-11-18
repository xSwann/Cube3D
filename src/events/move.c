#include "../../headers/cube3D.h"

static int	is_wall(t_scene *scene, double y, double x)
{
	int	xi;
	int	yi;

	yi = (int)y;
	xi = (int)x;
	if (yi < 0 || xi < 0 || yi >= scene->map_height)
		return (1);
	if (xi >= (int)ft_strlen(scene->map_tab[yi]))
		return (1);
	return (scene->map_tab[yi][xi] == '1');
}

static void	move_forward(t_app *app, double speed)
{
	double	new_y;
	double	new_x;

	new_y = app->player.pos_y + app->player.dir_y * speed;
	new_x = app->player.pos_x + app->player.dir_x * speed;
	if (!is_wall(&app->scene, new_y, app->player.pos_x))
		app->player.pos_y = new_y;
	if (!is_wall(&app->scene, app->player.pos_y, new_x))
		app->player.pos_x = new_x;
}

static void	move_backward(t_app *app, double speed)
{
	double	new_y;
	double	new_x;

	new_y = app->player.pos_y - app->player.dir_y * speed;
	new_x = app->player.pos_x - app->player.dir_x * speed;
	if (!is_wall(&app->scene, new_y, app->player.pos_x))
		app->player.pos_y = new_y;
	if (!is_wall(&app->scene, app->player.pos_y, new_x))
		app->player.pos_x = new_x;
}

static void	strafe_left(t_app *app, double speed)
{
	double	perp_x;
	double	perp_y;
	double	new_y;
	double	new_x;

	perp_x = app->player.dir_y;
	perp_y = -app->player.dir_x;
	new_y = app->player.pos_y + perp_y * speed;
	new_x = app->player.pos_x + perp_x * speed;
	if (!is_wall(&app->scene, new_y, app->player.pos_x))
		app->player.pos_y = new_y;
	if (!is_wall(&app->scene, app->player.pos_y, new_x))
		app->player.pos_x = new_x;
}

static void	strafe_right(t_app *app, double speed)
{
	double	perp_x;
	double	perp_y;
	double	new_y;
	double	new_x;

	perp_x = -app->player.dir_y;
	perp_y = app->player.dir_x;
	new_y = app->player.pos_y + perp_y * speed;
	new_x = app->player.pos_x + perp_x * speed;
	if (!is_wall(&app->scene, new_y, app->player.pos_x))
		app->player.pos_y = new_y;
	if (!is_wall(&app->scene, app->player.pos_y, new_x))
		app->player.pos_x = new_x;
}

static void	rotate_player(t_app *app, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = app->player.dir_x;
	app->player.dir_x = app->player.dir_x * cos(angle) - app->player.dir_y
		* sin(angle);
	app->player.dir_y = old_dir_x * sin(angle) + app->player.dir_y
		* cos(angle);
	old_plane_x = app->player.plane_x;
	app->player.plane_x = app->player.plane_x
		* cos(angle) - app->player.plane_y * sin(angle);
	app->player.plane_y = old_plane_x * sin(angle) + app->player.plane_y
		* cos(angle);
}

void	movement(t_app *app)
{
	double	speed;
	double	rot_speed;

	speed = 0.1;
	rot_speed = 0.05;
	if (app->keys[119] || app->keys[65362])
		move_forward(app, speed);
	if (app->keys[115] || app->keys[65364])
		move_backward(app, speed);
	if (app->keys[97])
		strafe_left(app, speed);
	if (app->keys[100])
		strafe_right(app, speed);
	if (app->keys[65363])
		rotate_player(app, rot_speed);
	if (app->keys[65361])
		rotate_player(app, -rot_speed);
	if (app->keys[65307])
		quit_game(app);
}
