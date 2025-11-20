/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanteno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 08:18:24 by elanteno          #+#    #+#             */
/*   Updated: 2025/11/20 11:38:30 by elanteno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cube3D.h"

/* 
// delta_dist_x et delta_dist_y représentent des distances « unitaires » que doit
// parcourir un rayon le long de sa trajectoire pour franchir une ligne de la
// grille. En pratique, ces deux valeurs restent constantes pour un rayon donné
// et servent à mettre à jour side_dist_x et side_dist_y dans la boucle DDA :
// chaque fois que l’on franchit une frontière verticale, on ajoute delta_dist_x
// à side_dist_x, et chaque fois qu’on franchit une frontière horizontale, on
// ajoute delta_dist_y à side_dist_y. Cela permet de progresser correctement
// dans la grille en tenant compte de l’angle du rayon : un rayon presque
// horizontal aura un delta_dist_x petit et un delta_dist_y très grand, et
// inversement pour un rayon presque vertical.
*/
static double	get_delta(double dir)
{
	double	inv;

	if (dir == 0.0)
		return (1e30);
	inv = 1.0 / dir;
	if (inv < 0.0)
		return (-inv);
	return (inv);
}

/*
 * init_ray : prépare les valeurs de base pour lancer un rayon sur la colonne x.
 * - camera_x : de -1 (gauche de l’écran) à +1 (droite) pour interpoler
 *   la direction.
 * - dir_x/dir_y : direction du rayon (direction du joueur + plan * camera_x).
 * - map_x/map_y : position du joueur convertie en indices de grille.
 * - delta_dist_x/delta_dist_y : distances à parcourir entre
 *   intersections (voir get_delta).
 * - hit : indique qu’on n’a pas encore rencontré de mur.
 */
void	init_ray(t_ray *ray, t_app *app, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIN_WIDTH - 1.0;
	ray->camera_x = camera_x;
	ray->dir_x = app->player.dir_x + app->player.plane_x * camera_x;
	ray->dir_y = app->player.dir_y + app->player.plane_y * camera_x;
	ray->map_x = (int)app->player.pos_x;
	ray->map_y = (int)app->player.pos_y;
	ray->delta_dist_x = get_delta(ray->dir_x);
	ray->delta_dist_y = get_delta(ray->dir_y);
	ray->hit = 0;
}

/*
 * init_dda : prépare les paramètres pour l’algorithme DDA
 * (Digital Differential Analyzer).
 * On détermine dans quel sens (±1) le rayon traverse la grille
 * pour les axes x et y.
 * `step_x` vaut +1 si le rayon va vers les cellules de droite (dir_x >= 0),
 * et -1 s’il va vers les cellules de gauche (dir_x < 0). De même, `step_y` vaut
 * +1 si le rayon se déplace vers le bas (dir_y >= 0) et -1 s’il se
 * déplace vers le haut.
 *
 * On calcule ensuite `side_dist_x` et `side_dist_y`, la distance à parcourir
 * depuis la position actuelle jusqu’à la première frontière verticale ou
 * horizontale. Ces distances initiales dépendent de la partie décimale de la
 * position du joueur :
 *
 * if (ray->dir_x < 0)
 * {
 *     ray->step_x = -1; // Le rayon se dirige vers la gauche
 * // Distance jusqu’à la première frontière verticale à gauche :
 * // on prend la différence entre la position en X du joueur et la
 * coordonnée entière map_x,
 *     // puis on la multiplie par delta_dist_x pour la convertir
 *     en distance le long du rayon.
 *     ray->side_dist_x = (app->player.pos_x - ray->map_x) * ray->delta_dist_x;
 * }
 * else
 * {
 *     ray->step_x = 1; // Le rayon se dirige vers la droite
 *     // Distance jusqu’à la prochaine frontière verticale à droite :
 * // (map_x + 1.0 - pos_x) représente l’écart horizontal jusqu’au bord
 * de la cellule,
 *     // multiplié par delta_dist_x pour obtenir la distance projetée.
 *ray->side_dist_x = (ray->map_x + 1.0 - app->player.pos_x) * ray->delta_dist_x;
 * }
 * if (ray->dir_y < 0)
 * {
 *     ray->step_y = -1; // Le rayon monte dans la grille
 *     // Distance jusqu’à la première frontière horizontale au-dessus.
 *     ray->side_dist_y = (app->player.pos_y - ray->map_y) * ray->delta_dist_y;
 * }
 * else
 * {
 *     ray->step_y = 1; // Le rayon descend dans la grille
 *     // Distance jusqu’à la prochaine frontière horizontale en dessous.
 *ray->side_dist_y = (ray->map_y + 1.0 - app->player.pos_y) * ray->delta_dist_y;
 * }
 */
void	init_dda(t_ray *ray, t_app *app)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (app->player.pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - app->player.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (app->player.pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - app->player.pos_y)
			* ray->delta_dist_y;
	}
}

/*
 * perform_dda : exécute l’algorithme DDA jusqu’à ce qu’un mur soit rencontré.
 * À chaque itération on avance vers la prochaine ligne de grille horizontale ou
 * verticale selon laquelle est la plus proche, et on vérifie si la case
 * contient un mur ('1').  On arrête quand ray->hit passe à 1.
*
 // Choisit la plus petite distance pour avancer
//         if (ray->side_dist_x < ray->side_dist_y)
// Si on sort de la carte, on déclenche une erreur
// Si la case courante est un mur, on marque l’impact
*/
void	perform_dda(t_ray *ray, t_app *app)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_y < 0
			|| ray->map_y >= app->scene.map_height
			|| ray->map_x >= (int)ft_strlen(app->scene.map_tab[ray->map_y]))
			error_handler("Raycasting out of map bounds");
		if (app->scene.map_tab[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}
