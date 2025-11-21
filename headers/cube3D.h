/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slatrech <slatrech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:24:34 by slatrech          #+#    #+#             */
/*   Updated: 2025/11/21 17:27:32 by slatrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

/* ************************************************************************** */
/*                                INCLUDES                                    */
/* ************************************************************************** */

# include "../src/get_next_line/get_next_line.h"
# include	"../headers/libft.h"
# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

/* ************************************************************************** */
/*                                DEFINES                                     */
/* ************************************************************************** */

# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define TEX_SIZE 64

# define RED "\033[1;31m"
# define RESET "\033[0m"

/* ************************************************************************** */
/*                               STRUCTURES                                   */
/* ************************************************************************** */

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bpp;
	int		line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_scene
{
	t_list	*map_struct;
	char	**map_tab;

	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;

	char	*floor_color;
	char	*ceiling_color;

	int		spawn_x;
	int		spawn_y;
	char	spawn_orientation;

	int		map_height;
	int		map_width;
}	t_scene;

typedef struct s_app
{
	void		*mlx;
	void		*win;

	t_img		frame;
	t_img		textures[4];

	t_scene		scene;
	t_player	player;

	int			ceiling_color;
	int			floor_color;

	int			keys[65536];
}	t_app;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;

	int		map_x;
	int		map_y;

	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;

	int		step_x;
	int		step_y;
	int		hit;
	int		side;

	double	perp_wall_dist;
}	t_ray;

typedef struct s_tex_calc
{
	t_img	*tex;
	int		tex_x;
	int		tex_y;
	double	wall_x;
	double	step;
	double	tex_pos;
}	t_tex_calc;

typedef struct s_fill
{
	char	**map;
	int		**visited;
	int		width;
	int		height;
}	t_fill;

/* ************************************************************************** */
/*                               PARSING                                      */
/* ************************************************************************** */

t_scene	parse_file(char *file_name);
void	read_scene_lines(int fd, t_scene *scene);

/* --- parsing utils --- */
void	remove_endl(char **str);
int		is_empty(char *str);
int		is_line_valid(char *line);
int		is_configuration_full(t_scene *scene);
int		is_spawn_tile(char c);
int		is_open_tile(char tile);
void	skip_spaces(int *i, char *line);

/* --- textures --- */
void	validate_textures(t_scene *scene);
void	import_configuration_line(char *line, t_scene *scene);
char	*sanitize_texture_line(char *line);

/* --- colors --- */
void	check_rgb_error(t_scene *scene, char *line, char *to_free, char *nb);
void	import_colors(char *line, int i, t_scene *scene);
char	*import_color_line(t_scene *scene, char *line, char *line_to_free);
char	*sanitize_color_line(char *line);
char	*find_full_number(char *line, int *i, int *count);
void	color_line_error(t_scene *scene, char *line, char *to_free, char *msg);
int		parse_rgb(char *str);
char	*clean_color_string(char *s);

/* --- map extraction --- */
int		put_map_in_list(char *map_line, t_scene *scene);
char	**put_list_in_tabs(t_list *map, int is_map);
int		list_size(t_list *list);
t_list	*create_node(char *line);
void	add_back(t_list **list, t_list *new_node);

/* --- map shaping & validation --- */
void	is_map_name_valid(char *map_name);
void	get_width_and_height(char **raw_map, t_scene *scene);
char	**uniform_map(char **map, int width, int height);
void	check_border(t_scene *scene);
void	find_spawn(t_scene *scene);

/* --- flood fill --- */
int		**alloc_visited(t_scene *scene);
void	init_fill_struct(t_fill *f, t_scene *scene, int **visited);
void	flood(t_scene *scene, t_fill *f, int x, int y);
void	border_flood_calls(t_scene *scene, t_fill *f);

/* *********************************************************************** */
/*                              FREE                                       */
/* *********************************************************************** */

void	free_scene_infos(t_scene *scene);
void	free_scene(t_scene *scene);
void	free_scene_and_exit(t_scene *scene, char *msg);
void	free_map(t_list *map);
void	free_tab(char **tab);
void	free_int_tab(int **tab, int height);
void	free_all_data(t_app *app);
void	free_textures(t_app *app);

/* *********************************************************************** */
/*                       RENDERING & MOVEMENT                              */
/* *********************************************************************** */

void	render_scene(t_app *app);
int		get_color(t_app *app, t_ray *ray, int y, int line_height);

/* --- movement --- */
void	movement(t_app *app);
int		is_wall(t_scene *scene, double y, double x);
void	move_forward(t_app *app, double speed);
void	move_backward(t_app *app, double speed);
void	strafe_left(t_app *app, double speed);
void	strafe_right(t_app *app, double speed);
void	rotate_player(t_app *app, double angle);

/* --- events --- */
int		key_press(int key, t_app *app);
int		key_release(int key, t_app *app);
int		quit_game(t_app *app);

/* *********************************************************************** */
/*                        RAYCASTING & INIT                                */
/* *********************************************************************** */

void	init_mlx(t_app *app);
void	init_img(t_app *app, t_img *image, int width, int height);
void	init_texture_img(t_app *app, t_img *image, char *path);
void	load_textures(t_app *app);

void	init_player(t_app *app);
void	init_player_dir(t_app *app, char dir);

void	init_ray(t_ray *ray, t_app *app, int x);
void	init_dda(t_ray *ray, t_app *app);
void	perform_dda(t_ray *ray, t_app *app);

/* *********************************************************************** */
/*                             UTILS                                       */
/* *********************************************************************** */

void	error_handler(char *msg);
void	print_tab(char **tab);
void	print_scene_infos(t_scene *scene);
void	ft_putstr_fd(char *s, int fd);
int		is_valid_path(const char *path);
void	copy_chars(int *i, int *j, char **copy_tab, char **tab);

#endif
