/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:14:35 by slatrech          #+#    #+#             */
/*   Updated: 2025/11/21 16:14:37 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3D.h"

int	loop(t_app *app)
{
	movement(app);
	render_scene(app);
	return (0);
}

int	main(int ac, char **av)
{
	t_app	app;

	if (ac != 2)
		error_handler("Usage: ./cub3D map.cub");
	is_map_name_valid(av[1]);
	ft_memset(&app, 0, sizeof(t_app));
	app.scene = parse_file(av[1]);
	app.floor_color = parse_rgb(app.scene.floor_color);
	app.ceiling_color = parse_rgb(app.scene.ceiling_color);
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
