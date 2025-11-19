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
	t_img	*tex;
	int		tex_x;
	int		tex_y;
	double	wall_x;
	double	step;
	double	tex_pos;
	int		tex_dir;

	if (ray->side == 0)
		wall_x = app->player.pos_y
			+ ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = app->player.pos_x
			+ ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_dir = 0;
	if (ray->side == 0 && ray->dir_x > 0)
		tex_dir = 0;
	else if (ray->side == 0 && ray->dir_x < 0)
		tex_dir = 1;
	else if (ray->side == 1 && ray->dir_y > 0)
		tex_dir = 2;
	else
		tex_dir = 3;
	tex = &app->textures[tex_dir];
	tex_x = (int)(wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	step = 1.0 * tex->height / line_height;
	tex_pos = (y - (-line_height / 2 + WIN_HEIGHT / 2)) * step;
	tex_y = (int)tex_pos & (tex->height - 1);
	return (tex->addr[tex_y * tex->width + tex_x]);
}
