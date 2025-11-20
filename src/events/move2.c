/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanteno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 07:50:32 by elanteno          #+#    #+#             */
/*   Updated: 2025/11/20 08:01:02 by elanteno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cube3D.h"

/*
 * move_forward : avance le joueur dans la direction où il regarde.  Calcule
 * les nouvelles coordonnées (new_x, new_y) en ajoutant le vecteur direction
 * multiplié par la vitesse.  On vérifie séparément les collisions sur y et x
 * pour permettre le glissement le long des murs.
 */
void	move_forward(t_app *app, double speed)
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

/*
 * l’inverse du vecteur direction.
 * Procède de la même manière que move_forward mais en soustrayant
 * la direction.
 */
void	move_backward(t_app *app, double speed)
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

/*
 * strafe_left : déplace le joueur perpendiculairement à sa direction, vers
 * la gauche.  Le vecteur perpendiculaire est obtenu en permutant dir_x/dir_y
 * et en inversant un signe.  Cette opération permet de faire un "strafe".
 */
void	strafe_left(t_app *app, double speed)
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

/*
 * strafe_right : déplace le joueur perpendiculairement vers la droite.
 * Le vecteur perpendiculaire change simplement de signe par rapport à
 * strafe_left.
 */
void	strafe_right(t_app *app, double speed)
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

/*
 * rotate_player : fait pivoter le vecteur direction et le plan caméra
 * d’un angle donné (en radians).  On sauvegarde d’abord l’ancienne valeur
 * puis on applique les formules de rotation 2D.  Cela permet de tourner
 * la vue sans changer la position du joueur.
 */
void	rotate_player(t_app *app, double angle)
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
