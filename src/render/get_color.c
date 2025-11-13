#include "../../headers/cube3D.h"

/* get_color(t_app *app, t_ray *ray, int y, int line_height) : met à jour le rendu de la frame courante. */
/* avance rayon par rayon pour détecter les intersections → échantillonne la texture au bon offset. */
/* met à jour le tampon d'image. */
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

