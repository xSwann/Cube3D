#include "../../headers/cube3D.h"

void	init_img(t_app *app, t_img *image, int width, int height)
{
	image->img = mlx_new_image(app->mlx, width, height);
	if (!image->img)
		error_handler("Image creation failed");
	image->addr = (int *)mlx_get_data_addr(image->img, &image->bpp,
			&image->line, &image->endian);
	if (!image->addr)
		error_handler("Image data access failed");
	image->width = width;
	image->height = height;
}

void	init_texture_img(t_app *app, t_img *image, char *path)
{
	if (!path || !*path)
		return ;
	image->img = mlx_xpm_file_to_image(app->mlx, path, &image->width,
			&image->height);
	if (!image->img)
		error_handler("Texture loading failed");
	image->addr = (int *)mlx_get_data_addr(image->img, &image->bpp,
			&image->line, &image->endian);
	if (!image->addr)
		error_handler("Texture data access failed");
}

void	init_mlx(t_app *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		error_handler("MLX initialization failed");
	app->win = mlx_new_window(app->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!app->win)
		error_handler("Window creation failed");
	init_img(app, &app->frame, WIN_WIDTH, WIN_HEIGHT);
}
