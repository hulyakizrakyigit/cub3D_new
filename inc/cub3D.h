# ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../lib/libft/get_next_line/get_next_line.h"
# include "../lib/libmlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <math.h> 

# define WIDTH 640
# define HEIGHT 480

# define RAY_ERROR 0.000001f

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum 
{
	NoEventMask = 0L,
	KeyPressMask = 1L<<0,
	KeyReleaseMask = 1L<<1,
	ButtonPressMask	= 1L<<2,
	ButtonReleaseMask = 1L<<3,
	EnterWindowMask	= 1L<<4,
	LeaveWindowMask = 1L<<5,
	PointerMotionMask = 1L<<6,
	PointerMotionHintMask = 1L<<7,
	Button1MotionMask = 1L<<8,
	Button2MotionMask = 1L<<9,
	Button3MotionMask = 1L<<10,
	Button4MotionMask = 1L<<11,
	Button5MotionMask = 1L<<12,
	ButtonMotionMask = 1L<<13,
	KeymapStateMask = 1L<<14,
	ExposureMask = 1L<<15,
	VisibilityChangeMask = 1L<<16,
	StructureNotifyMask = 1L<<17,
	ResizeRedirectMask = 1L<<18,
	SubstructureNotifyMask = 1L<<19,
	SubstructureRedirectMask = 1L<<20,
	FocusChangeMask = 1L<<21,
	PropertyChangeMask = 1L<<22,
	ColormapChangeMask = 1L<<23,
	OwnerGrabButtonMask = 1L<<24
};

# define ARROW_UP 		126
# define ARROW_DOWN		125
# define ARROW_LEFT		123
# define ARROW_RIGHT	124
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define ESC_KEY		53
# define KEY_Q			12

# define ANGLE_STEP		0.02f
# define LINEAR_STEP	0.3f
# define FOV			1.047f // Field Of Vision 60 degrees
# define MAP_SCALE		4

typedef enum e_err
{
	OK = 0,
	ERR = 1
}	t_err;

typedef struct s_ray
{
	float	dx;
	float	dy;
	int		sx;
	int		sy;
	float	hor_x;
	float	hor_y;
	float	vert_x;
	float	vert_y;
	float	vert_dist;
	float	hor_dist;
	float	vert_w;
	float	hor_w;
}	t_ray;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	char	*path;
	int		count;
	int		width;
	int		height;
}	t_img;


typedef struct s_color
{
	int		R;
	int		G;
	int		B;
	int		count;
	char	*rgb_str;
	char	**rgb_str_arr;

}	t_color;

typedef struct s_texture
{
	t_img	NO;
	t_img	SO;
	t_img	WE;
	t_img	EA;
	t_color	F;
	t_color	C;

}	t_texture;

typedef struct s_player
{
	int		x;
	int		y;
	char	direction;
}	t_player;

typedef struct s_map
{
	char		**map;
	char		**map_H;
	t_texture	texture;
	char		*path;
	int			row;
	int			map_len;
	int			map_width;
	int			map_height;
	int			map_start;
	int			map_end;
	int			player_count;
	t_player	player;
}	t_map;

typedef struct s_image
{
	void	*east;
	void	*north;
	void	*south;
	void	*west;
}	t_image;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_game
{
	t_map	map;
	t_map	pure_map;
	t_map	map_last;
	t_image	image;
	t_mlx	mlx;
	t_img	img_w;
	float	pos_x;
	float	pos_y;
	float	angle_view;
	t_img	txt[4];
	int		txt_idx;
	float	txt_w;
	int		color_ceiling;
	int		color_floor;
	t_map	last_map;
}	t_game;

// err.c
t_err	perr(const char *func, const char *msg);

//init.c
t_err	game_init(t_game *game, char *path);
t_err	map_path_control(char *path);
t_err	prepare_map_init(t_map *map, char *path);

//control_map_items.c
t_err	map_control_centrals_items(t_map *map, char *line, int x);
t_err	map_control_centrals(t_map *map);
int		map_width(t_map *map);
t_err	map_H(t_map *map);
t_err	control_player(t_map *map);

//control_map.c
t_err	is_map_valid(char **map);
t_err	validate_map(char **map);
t_err	map_control_part(t_map *map);
t_err	map_control(t_map *map);

//helper.c
void	flood_fill(char **map, int x, int y);
bool	is_one_or_space(char c);
bool	all_chars_are(char *str);

//init_texture.c
t_err	texture_init(t_map *map, char *path);
t_err	control_texture_color(t_color *color);
t_err	is_invalid_color(char **rgb_str_arr);
t_err	check_texture_color(char *line, t_map *map);

//set_texture.c
t_err	control_texture_dir(t_texture *texture);
t_err	set_texture(char *line, t_map *map);
void	set_texture_dir(char *line, t_map *map);
void	set_texture_color_F(t_texture *texture);
void	set_texture_color_C(t_texture *texture);

//str_utils.c
bool	strevery(int (*func)(int c), const char *str);
bool	is_empty_line(char *line);

//dispose.c
void	dispose(t_game *game);
void	strr_arr_dispose(char **arr);

//
t_err	init_mlx(t_game *game);
int		close_window(t_game *game);
int		esc_press(int keycode, t_game *game);

//
t_err	image_up(t_game *game);

//start_game.c
void	resoures_initialisation(t_game *game);
void	set_angle_view(t_game *game);
void	set_position(t_game *game);
void	start_game(t_game *game);
void	draw(t_game *game);
void	draw_ceiling_and_floor(t_game *game);

//key_hook.c
int		destroy_exit(t_game *game);
void	move(t_game *game, int direction);
float	ray(t_game *game, float v);
void	move(t_game *game, int direction);
int		key(int keycode, t_game *game);

void	ray_initial_calculations(t_game *game, t_ray *r, float v);
int		sign(float f);
void	ray_next_step_calculation(t_game *game, t_ray *r);
float	save_color(t_game *game, float dist, int color_idx, float w);
void initialize_pure_map(t_game *game);
t_err allocate_map_H(t_map *map);
t_err map_H_fill(t_map *map);
t_err map_control_set_player(t_map *map, int x, int y, char direction);
t_err map_control_boundaries(t_map *map);
t_err validate_map_start(char **map, int *start_x, int *start_y);
t_err prepare_map_init_part1(t_map *map, char *path, int *fd);
t_err prepare_map_init_part2(t_map *map, int fd);
float ray_initial_part(t_game *game, float v, t_ray *r);
float ray_next_steps_part(t_game *game, t_ray *r);
float ray_check_vertical(t_game *game, t_ray *r);
float ray_check_horizontal(t_game *game, t_ray *r);
void set_texture_for_direction(char *line, t_map *map, t_img *texture);


t_game	*initialize_game(void);
t_err	run_map_checks(t_game *game, char *path);
void	initialize_and_run_game(t_game *game);
char		**pure_map(char **map, int height);
void	set_player(t_game *game);
void	ray_casting(t_game *game);
void load_textures(t_game *game);
void load_textures_addresses(t_game *game);


#endif
