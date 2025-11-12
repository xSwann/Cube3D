#include "../headers/cube3D.h"

int	loop(t_app *app)
{
	movement(app);
	render_scene(app);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	return (0);
}

static int	get_map_width(char **map)
{
	int	i;
	int	len;
	int	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

void	parse_map_tab(t_scene *scene)
{
	int	y;
	int	x;

	scene->map_height = 0;
	while (scene->map[scene->map_height])
		scene->map_height++;

	scene->map_width = get_map_width(scene->map);
	scene->map_tab = malloc(sizeof(char *) * (scene->map_height + 1));
	if (!scene->map_tab)
		error_handler("Failed to allocate map_tab");

	y = -1;
	while (++y < scene->map_height)
	{
		scene->map_tab[y] = ft_calloc(scene->map_width + 1, sizeof(char));
		if (!scene->map_tab[y])
			error_handler("Failed to allocate map_tab[y]");
		x = -1;
		while (scene->map[y][++x])
			scene->map_tab[y][x] = scene->map[y][x];
	}
	scene->map_tab[scene->map_height] = NULL;
}

int	main(int ac, char **av)
{
	t_app	app;

	if (ac != 2)
		error_handler("Usage: ./cub3D map.cub");
	ft_memset(&app, 0, sizeof(t_app));
	app.mlx = mlx_init();
	app.win = mlx_new_window(app.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	app.scene = parse_file(av[1]);
	parse_map_tab(&app.scene);
	init_mlx(&app);
	load_textures(&app);
	init_player(&app);
	mlx_hook(app.win, 2, 1L << 0, key_press, &app);
	mlx_hook(app.win, 3, 1L << 1, key_release, &app);
	mlx_hook(app.win, 33, 1L << 17, quit_game, &app);
	mlx_loop_hook(app.mlx, loop, &app);
	mlx_loop(app.mlx);
	return (0);
}
