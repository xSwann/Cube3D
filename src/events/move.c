#include "../../headers/cube3D.h"

/*
 * is_wall : détermine si la case aux coordonnées (x, y) contient un mur ou si
 * elle est en dehors des limites de la carte. Renvoie 1 si la cellule n’est
 * pas franchissable (mur ou bord de carte), sinon 0.
 * 	yi = (int)y;  // Convertit la position flottante en indice de ligne.
 * 	xi = (int)x;  // Convertit la position flottante en indice de colonne.
 */
int	is_wall(t_scene *scene, double y, double x)
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

/*
 * movement : fonction appelée à chaque frame pour mettre à jour la position
 * et l’orientation du joueur selon les touches pressées.  Elle définit la
 * vitesse de déplacement (speed) et de rotation (rot_speed), puis teste
 * l’état des touches dans le tableau app->keys pour déclencher les actions.
 */
void	movement(t_app *app)
{
	double	speed;
	double	rot_speed;

	speed = 0.02;
	rot_speed = 0.01;
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
