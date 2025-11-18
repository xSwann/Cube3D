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

/* init_ray(t_ray *ray, t_app *app, int x) : initialise les structures valeurs nécessaires. */
/* avance rayon par rayon pour détecter les intersections. */
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

/* init_dda(t_ray *ray, t_app *app) : initialise les structures et valeurs nécessaires. */
/* Elle valide ses entrées (pointeurs, bornes, tailles) et sort tôt en cas d'entrée invalide. */
void init_dda(t_ray *ray, t_app *app)
{
    if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (app->player.pos_x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - app->player.pos_x) * ray->delta_dist_x;
    }
    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (app->player.pos_y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - app->player.pos_y) * ray->delta_dist_y;
    }
}

/* perform_dda(t_ray *ray, t_app *app) : met à jour le rendu de la frame courante. */
void perform_dda(t_ray *ray, t_app *app)
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
		if (ray->map_x < 0 || ray->map_y < 0 ||
				ray->map_y >= app->scene.map_height ||
				ray->map_x >= (int)ft_strlen(app->scene.map_tab[ray->map_y]))
        error_handler("Raycasting out of map bounds");
        if (app->scene.map_tab[ray->map_y][ray->map_x] == '1')
            ray->hit = 1;
    }
}

/* my_mlx_pixel_put(t_img *img, int x, int y, int color) : met à jour le rendu de la frame courante. */
void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = (char *)img->addr + (y * img->line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
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
	line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
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

/* render_scene(t_app *app) : calcule et écrit le rendu (pixels, lignes ou primitives). */
void render_scene(t_app *app)
{
    int x;
    t_ray ray = {0};

    x = 0;
    while (x < WIN_WIDTH)
    {
        init_ray(&ray, app, x);
        init_dda(&ray, app);
        perform_dda(&ray, app);
        if (ray.side == 0)
            ray.perp_wall_dist = (ray.map_x - app->player.pos_x + (1 - ray.step_x) / 2) / ray.dir_x;
        else
            ray.perp_wall_dist = (ray.map_y - app->player.pos_y + (1 - ray.step_y) / 2) / ray.dir_y;
        draw_column(app, x, &ray);
        x++;
    }
    mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
}
