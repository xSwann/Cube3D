#include "../../headers/cube3D.h"
#include "../../headers/libft.h"

void	error_handler(char *error_message)
{
	ft_putstr_fd(RED "cub3D: Error: ", 2);
	ft_putstr_fd(error_message, 2);
	ft_putstr_fd("\n" RESET, 2);
	exit(EXIT_FAILURE);
}

void	super_exit(t_app *app, int code)
{
	if (!app)
		exit(code);
	if (app->win && app->mlx)
		mlx_destroy_window(app->mlx, app->win);
	if (app->mlx)
	{
		mlx_destroy_display(app->mlx);
		mlx_loop_end(app->mlx);
		free(app->mlx);
	}
	free_all_data(app);
	exit(code);
}

int	err_msg_detail(char *detail, char *str, int code)
{
	ft_putstr_fd(RED "cub3D: Error", 2);
	if (detail)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(detail, 2);
	}
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putstr_fd("\n" RESET, 2);
	return (code);
}

int	quit_game(t_app *app)
{
	super_exit(app, 0);
	return (0);
}

void	free_textures(t_app *app)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (app->textures[i].img)
			mlx_destroy_image(app->mlx, app->textures[i].img);
		i++;
	}
}

void	free_image(t_app *app)
{
	if (app->frame.img)
		mlx_destroy_image(app->mlx, app->frame.img);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_scene(t_scene *scene)
{
	if (scene->no_texture)
		free(scene->no_texture);
	if (scene->so_texture)
		free(scene->so_texture);
	if (scene->we_texture)
		free(scene->we_texture);
	if (scene->ea_texture)
		free(scene->ea_texture);
	if (scene->floor_color)
		free(scene->floor_color);
	if (scene->ceiling_color)
		free(scene->ceiling_color);
	free_map(scene->map_tab);
}

void	free_all_data(t_app *app)
{
	free_textures(app);
	free_image(app);
	free_scene(&app->scene);
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	if (app->mlx)
	{
		mlx_destroy_display(app->mlx);
		free(app->mlx);
	}
}

