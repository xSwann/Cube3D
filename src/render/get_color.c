/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:15:35 by slatrech          #+#    #+#             */
/*   Updated: 2025/11/21 16:15:36 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cube3D.h"

/*
 *  * get_color : renvoie la couleur du pixel situé à la position (x, y) dans
 *  la colonneen cours de rendu. La fonction sélectionne la bonne texture
 *  selon la face du mur
 * touchée, calcule la coordonnée horizontale dans cette texture (tex_x),
 * puis la coordonnée verticale (tex_y) en fonction de la hauteur du mur affiché

	// Déterminer la position de l’impact du rayon sur le mur.
	// Si le mur touché est vertical (side == 0), l’impact dépend de la
	// coordonnée y du joueur.
	// Sinon, il dépend de la coordonnée x. On multiplie par la
	// distance perpendiculaire pour
	// retrouver le point exact d’intersection.

	// Choisir la texture en fonction de la face du mur et du sens du rayon :
	// - face verticale et rayon allant vers l’est => texture nord
	// - face verticale et rayon allant vers l’ouest => texture sud
	// - face horizontale et rayon allant vers le sud => texture ouest
	// - sinon => texture est

	// Convertir wall_x en une coordonnée horizontale de texture :
	// Pour certaines orientations (rayon allant vers la droite ou vers le haut)
	// il faut inverser l’axe x pour éviter que la texture ne soit affichée à
	// l’envers.

	// La coordonnée y dans la texture est obtenue en prenant la partie
	// entière de tex_pos.
	// L’opérateur & (bitwise AND) avec (tex->height - 1) d’alternative rapide
	// à un modulo.
	// Enfin, on renvoie la couleur du pixel (tex_x, tex_y) dans la texture.
*/
int	get_color(t_app *app, t_ray *ray, int y, int line_height)
{
	t_tex_calc	tc;
	int			start;

	tc.wall_x = app->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	if (ray->side == 0)
		tc.wall_x = app->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	tc.wall_x -= floor(tc.wall_x);
	if (ray->side == 0 && ray->dir_x > 0)
		tc.tex = &app->textures[0];
	else if (ray->side == 0 && ray->dir_x < 0)
		tc.tex = &app->textures[1];
	else if (ray->side == 1 && ray->dir_y > 0)
		tc.tex = &app->textures[2];
	else
		tc.tex = &app->textures[3];
	tc.tex_x = (int)(tc.wall_x * (double)tc.tex->width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		tc.tex_x = tc.tex->width - tc.tex_x - 1;
	tc.step = 1.0 * tc.tex->height / line_height;
	start = -line_height / 2 + WIN_HEIGHT / 2;
	tc.tex_pos = (y - start) * tc.step;
	tc.tex_y = (int)tc.tex_pos & (tc.tex->height - 1);
	return (tc.tex->addr[tc.tex_y * tc.tex->width + tc.tex_x]);
}
