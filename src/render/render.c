#include "../../headers/cube3D.h"

/*
 * my_mlx_pixel_put : écrit un pixel de couleur `color` aux coordonnées (x, y)
 * dans l’image `img`.  On calcule l’adresse du pixel dans le buffer puis on
 * écrit la valeur entière (4 octets) à cet emplacement.
 */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = (char *)img->addr + (y * img->line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/*
 * draw_column : dessine une colonne verticale de l’écran pour un rayon donné.
 * Le mur est centré à l’écran en fonction de sa distance (perp_wall_dist).
 * La partie au‑dessus du mur est remplie de la couleur du plafond, la partie
 * au‑dessous de celle du sol, et la portion du mur est texturée via get_color()
 *
	int line_height; // Hauteur du mur projeté à l’écran
    int draw_start; // Position y de début du mur (limite haute)
    int draw_end; // Position y de fin du mur (limite basse)
    int y; // Compteur vertical pour parcourir la colonne
    int color; // Couleur du pixel à dessiner

// Si la distance perpendiculaire est nulle ou négative, on ne dessine rien
// line_height Calcule la hauteur du mur en fonction de la distance
// (plus loin = plus petit)
// draw_start Positionne le haut du mur pour que l’image soit centrée
// verticalement
// if (draw_start < 0) // Si le début est au-dessus de l’écran,
// on l’ajuste  draw_start = 0;

 y = 0; // Commence au pixel supérieur de la colonne
    while (y < WIN_HEIGHT) // Parcours de chaque pixel verticalement
    {
        if (y < draw_start) // Si on est au-dessus du mur
            color = app->ceiling_color; // On utilise la couleur du plafond
        else if (y > draw_end) // Si on est en dessous du mur
            color = app->floor_color; // On utilise la couleur du sol
        else
            color = get_color(app, ray, y, line_height);
// Sinon on calcule la couleur texturée du mur
        my_mlx_pixel_put(&app->frame, x, y, color);
// On dessine le pixel dans l’image finale
        y++; // Passe au pixel suivant
*/
static void	compute_draw_limits(t_ray *ray, int *line_height,
		int *draw_start, int *draw_end)
{
	*line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	*draw_start = -(*line_height) / 2 + WIN_HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = *line_height / 2 + WIN_HEIGHT / 2;
	if (*draw_end >= WIN_HEIGHT)
		*draw_end = WIN_HEIGHT - 1;
}

void	draw_column(t_app *app, int x, t_ray *ray)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	y;
	int	color;

	if (ray->perp_wall_dist <= 0)
		return ;
	compute_draw_limits(ray, &line_height, &draw_start, &draw_end);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y < draw_start)
			color = app->ceiling_color;
		else if (y > draw_end)
			color = app->floor_color;
		else
			color = get_color(app, ray, y, line_height);
		my_mlx_pixel_put(&app->frame, x, y, color);
		y++;
	}
}

/*
 * Dans l’algorithme DDA, on s’intéresse à la distance que doit parcourir
 * un rayon entre deux lignes de la grille, indépendamment du sens
 * de déplacement. Cette distance est appelée delta distance et se déduit
 * de la géométrie : on peut montrer que, pour un pas en X,
 * la longueur du segment de rayon vaut une formule compliqué...
// Prépare le rayon pour la colonne courante
// Initialise les variables pour le DDA
// Avance le rayon dans la carte jusqu’à toucher un mur
// if (ray.side == 0) Si le mur touché est vertical
// Calcule la distance perpendiculaire en fonction du pas x
// Sinon, le mur est horizontal
// Calcule la distance perpendiculaire en fonction du pas y
// Dessine la colonne à l’écran en fonction de la distance trouvée
// puis x++;  Passe à la colonne suivante
*/
void	render_scene(t_app *app)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(&ray, app, x);
		init_dda(&ray, app);
		perform_dda(&ray, app);
		if (ray.side == 0)
			ray.perp_wall_dist = (ray.map_x - app->player.pos_x
					+ (1 - ray.step_x) / 2) / ray.dir_x;
		else
			ray.perp_wall_dist = (ray.map_y - app->player.pos_y
					+ (1 - ray.step_y) / 2) / ray.dir_y;
		draw_column(app, x, &ray);
		x++;
	}
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
}
