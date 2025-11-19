#include "../../headers/cube3D.h"

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
