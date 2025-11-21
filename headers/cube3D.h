#ifndef CUBE3D_H
# define CUBE3D_H

# include "../src/get_next_line/get_next_line.h"
# include "../headers/libft.h"
# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define TEX_SIZE 64

# define RED "\033[1;31m"
# define RESET "\033[0m"

/*
	 * A wrapper around an MLX image.  The `img` pointer is the
	 * opaque handle returned by mlx_new_image() or mlx_xpm_file_to_image().
	 * `addr` points to the pixel buffer for direct per‑pixel writes (32‑bit
	 * colour values).  `bpp` (bits per pixel) and `line` (bytes per
	 * scanline) are filled by mlx_get_data_addr() and describe the
	 * underlying memory layout.  `endian` indicates the byte order (0
	 * for little endian, 1 for big endian).  `width` and `height`
	 * store the dimensions of the image in pixels.
	 */
typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bpp;
	int		line;
	int		endian;
	int		width;
	int		height;
}				t_img;

/*
	 * Represents the player’s state within the world.  `pos_x` and
	 * `pos_y` are the player’s current position in map units (double
	 * precision for smooth movement).  `dir_x` and `dir_y` form a unit
	 * vector pointing in the direction the player is facing.  The
	 * camera plane (`plane_x`, `plane_y`) is perpendicular to the
	 * direction vector and scaled to control the field of view: it is
	 * used to compute the direction of rays across the screen.
	 */
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}				t_player;

/*
	 * A node in a singly linked list used to accumulate lines of the
	 * map during parsing.  Each node contains one line of the map
	 * (`line`) and a pointer to the next node (`next`).  Using a
	 * linked list allows building the map incrementally without
	 * knowing its size beforehand.
	 */
typedef struct s_list
{
	char			*line;
	struct s_list	*next;
}			t_list;

/*
	 * Holds all of the data extracted from the .cub configuration
	 * file.  `map_struct` is a linked list of the raw map lines read
	 * from the file.  After parsing, these lines are copied into
	 * `map_tab`, which is a NULL‑terminated array of strings where
	 * each element represents a row of the map; rows are padded with
	 * spaces so that all have equal length.  The `no_texture`,
	 * `so_texture`, `we_texture` and `ea_texture` pointers store the
	 * file paths to the wall textures for the north, south, west and
	 * east walls, respectively.  `floor_color` and
	 * `ceiling_color` store the RGB strings for the floor and ceiling
	 * colours prior to conversion into integers.
	 *
	 * The spawn information (`spawn_x`, `spawn_y`, `spawn_orientation`)
	 * records where and in which direction the player should start.
	 * Finally, `map_height` and `map_width` hold the dimensions of the
	 * map after uniforming (number of rows and columns).
	 */
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
}			t_scene;

/*
	 * Central structure aggregating everything needed to run the
	 * application.  `mlx` is the pointer returned by mlx_init() and
	 * represents the connection to the X server.  `win` points to
	 * the application window created by mlx_new_window().  `frame`
	 * is an off‑screen image used as a framebuffer; the scene is
	 * rendered into this image each frame and then blitted to the
	 * window.
	 *
	 * `textures` holds the four wall textures loaded from disk.
	 * `scene` contains the parsed map and configuration.  `player`
	 * stores the player’s position, direction and camera plane.  The
	 * integer `ceiling_color` and `floor_color` store the 24‑bit RGB
	 * colours for the ceiling and floor after parsing.  Finally,
	 * `keys` is a large array used to track keyboard input by key
	 * code: each element is set to 1 when a key is pressed and 0
	 * when released.
	 */
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
}				t_app;

/*
	 * Represents a single ray cast through the world during rendering.
	 * For each vertical column of the screen, one t_ray instance is
	 * filled and used to detect the distance to the closest wall.  The
	 * `camera_x` field stores the horizontal coordinate on the
	 * projection plane (ranging from -1 on the left to +1 on the right).
	 * `dir_x` and `dir_y` are the direction components of the ray,
	 * computed from the player’s direction and camera plane.  `map_x`
	 * and `map_y` identify which square of the map grid the ray is
	 * currently within.
	 *
	 * `side_dist_x` and `side_dist_y` store the distance from the
	 * ray’s origin to the next x‑side and y‑side intersection of the
	 * grid, respectively.  `delta_dist_x` and `delta_dist_y` give the
	 * distance the ray has to travel along its path to cross one
	 * additional x‑side or y‑side.  `step_x` and `step_y` are set
	 * to either -1 or +1 and indicate in which direction the ray steps
	 * through the grid along the x and y axes.  `hit` becomes non‑zero
	 * when the DDA algorithm finds a wall cell.  `side` records
	 * whether the wall hit was vertical (0) or horizontal (1).
	 * `perp_wall_dist` holds the perpendicular distance from the
	 * player to the wall, which is used to compute the slice height
	 * on the screen.
	 */
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
}				t_ray;

/*
 * t_tex_calc : regroupe toutes les valeurs nécessaires au calcul
 * de la couleur du pixel texturé dans get_color().
 *
 * tex      → pointeur vers la texture sélectionnée (NO, SO, WE ou EA)
 * tex_x    → position horizontale dans la texture (coordonnée X du pixel)
 * tex_y    → position verticale dans la texture (coordonnée Y du pixel)
 * wall_x   → position exacte de l’impact du rayon sur le mur (entre 0 et 1)
 * step     → incrément vertical dans la texture pour chaque pixel à l’écran
 * tex_pos  → position verticale accumulée dans la texture (double)
 */
typedef struct s_tex_calc
{
	t_img	*tex;
	int		tex_x;
	int		tex_y;
	double	wall_x;
	double	step;
	double	tex_pos;
}	t_tex_calc;

/*
 * Parsing.
 */
t_scene	parse_file(char *file_name);
void	free_scene_infos(t_scene *scene);
int		put_map_in_list(char *map_line, t_list **map);
//flood fill
typedef struct s_fill
{
    char    **map;
    int     **visited;
    int      width;
    int      height;
}   t_fill;


//PARSING
int		**alloc_visited(t_scene *scene);
void	color_line_error(t_scene *scene, char *line, char *to_free, char *msg);
void	check_rgb_error(t_scene *scene, char *line, char *to_free, char *nb);
char	*find_full_number(char *line, int *i, int *count);
char	*sanitize_color_line(char *line);
void	import_colors(char *line, int i, t_scene *scene);
void	check_rgb_error(t_scene *scene, char *line, char *to_free, char *nb);
void	import_configuration_line(char *line, t_scene *scene);
void	init_fill_struct(t_fill *f, t_scene *scene, int **visited);
char	*sanitize_texture_line(char *line);
void	border_flood_calls(t_scene *scene, t_fill *f);
void    copy_chars(int *i, int *j, char **copy_tab, char **tab);
void	validate_textures(t_scene *scene);
void	skip_spaces(int *i, char *line);
int		is_line_valid(char *line);
int 	is_empty(char *str);
void 	remove_endl(char **str);
int 	is_configuration_full(t_scene *scene);
int		is_spawn_tile(char c);
t_scene parse_file(char *file_name);
void    flood(t_scene *scene, t_fill *f, int x, int y);
void    free_scene_infos(t_scene *scene);
void	print_list(t_list *list);
void	print_tab(char **tab);
void	print_scene_infos(t_scene *scene);
void	is_map_name_valid(char *map_name);
void	print_scene(t_scene *scene);
int 	is_open_tile(char tile);
void	free_scene(t_scene *scene);
char	**put_list_in_tabs(t_list *map, int is_map);
int		list_size(t_list *list);
void	add_back(t_list **list, t_list *new_node);
void	free_scene_and_exit(t_scene *scene, char *msg);
t_list	*create_node(char *line);
void	validate_textures(t_scene *scene);
void	read_scene_lines(int fd, t_scene *scene);
void	validate_map(char **map, int width, int height);
void	get_width_and_height(char **raw_map, t_scene *scene);
char	**uniform_map(char **map, int width, int height);
void	find_spawn(t_scene *scene);
int		parse_rgb(char *str);
char	*clean_color_string(char *s);

/*
 * Free.
 */
int		put_map_in_list(char *map_line, t_scene *scene);
void	read_scene_lines(int fd, t_scene *scene);
void    check_border(t_scene *scene);
void	get_width_and_height(char **raw_map, t_scene *scene);
char	**uniform_map(char **map, int width, int height);
//


//FREE
void	free_map(t_list *map);
void	free_tab(char **tab);
void	free_all_data(t_app *app);
void	free_textures(t_app *app);

/*
 * Rendering / movement / events.
 */
void	render_scene(t_app *app);
void	movement(t_app *app);
int		is_wall(t_scene *scene, double y, double x);
void	move_forward(t_app *app, double speed);
void	move_backward(t_app *app, double speed);
void	strafe_left(t_app *app, double speed);
void	strafe_right(t_app *app, double speed);
void	rotate_player(t_app *app, double angle);
int		key_press(int key, t_app *app);
int		key_release(int key, t_app *app);
int		quit_game(t_app *app);

/*
 * Raycasting / init.
 */
void	init_ray(t_ray *ray, t_app *app, int x);
void	init_dda(t_ray *ray, t_app *app);
void	perform_dda(t_ray *ray, t_app *app);
void	init_mlx(t_app *app);
void	load_textures(t_app *app);
void	init_player_dir(t_app *app, char dir);
void	init_player(t_app *app);

/*
 * Utils.
 */
void	error_handler(char *msg);
int		get_color(t_app *app, t_ray *ray, int y, int line_height);
void	ft_putstr_fd(char *s, int fd);
void	init_texture_img(t_app *app, t_img *image, char *path);
int		is_valid_path(const char *path);
void	init_img(t_app *app, t_img *image, int width, int height);

#endif
