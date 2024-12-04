#include "cub3D.h"
#include <math.h>

int	destroy_exit(t_game *game)
{
	// int	i;

	// if (game->mlx.win)
	// 	mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	// // mlx_destroy_image(game->mlx.mlx, game->img_w.img);
	// mlx_destroy_image(game->mlx.mlx, game->wall_img.img);
	// i = -1;
	// while (++i < 4)
	// 	if (game->txt[i].img)
	// 		mlx_destroy_image(game->mlx.mlx, game->txt[i].img);
	dispose(game);
	exit(0);
}

float	ray(t_game *game, float v)
{
	t_ray	r;

	ray_initial_calculations(game, &r, v);

	while (1)
	{
		ray_next_step_calculation(game, &r);

		if (r.vert_dist < r.hor_dist)
		{
			int index_x = (int)r.vert_x + (r.sx - 1) / 2;
			// printf("index_x : %d\n", index_x);
			// printf("r.vert_y : %f\n", r.vert_y);

			if (index_x < 0 || index_x >= game->pure_map.map_width - 1)
				return (INFINITY);

			if ((int)r.vert_y < 0 || (int)r.vert_y >= game->pure_map.map_height - 1)
				return (INFINITY);
			printf("XXXXXXXXgame->pure_map.map[(int)r.vert_y][index_x] : %c\n", game->pure_map.map[(int)r.vert_y][index_x]);
			if (game->pure_map.map[(int)r.vert_y][index_x] == '1')
				return (save_color(game, r.vert_dist, r.sx + 1, r.vert_w));
			else
				r.vert_x += r.sx;
		}
		else
		{
			int index_y = (int)r.hor_y + (r.sy - 1) / 2;
			// printf("index_y : %d\n", index_y);
			// printf("r.hor_x : %f\n", r.hor_x);
			if ((int)r.hor_x < 0 || (int)r.hor_x >= game->pure_map.map_width - 1)
				return (INFINITY);

			if (index_y < 0 || index_y >= game->pure_map.map_height - 1)
				return (INFINITY);
			printf("YYYYYYYYgame->pure_map.map[index_y][(int)r.hor_x] : %c\n", game->pure_map.map[index_y][(int)r.hor_x]);
			if (game->pure_map.map[index_y][(int)r.hor_x] == '1')
				return (save_color(game, r.hor_dist, r.sy + 2, r.hor_w));
			else
				r.hor_y += r.sy;
		}
	}
}
// float	ray(t_game *game, float v)
// {
// 	t_ray	r;

// 	ray_initial_calculations(game, &r, v);
// 	while (1)
// 	{
// 		ray_next_step_calculation(game, &r);
// 		if (r.vert_dist < r.hor_dist)
// 		{
// 			if (game->pure_map.map[(int)r.vert_y][(int)r.vert_x + (r.sx - 1) / 2] == '1')
// 				return (save_color(game, r.vert_dist, r.sx + 1, r.vert_w));
// 			else
// 				r.vert_x += r.sx;
// 		}
// 		else
// 		{
// 			if (game->pure_map.map[(int)r.hor_y + (r.sy - 1) / 2][(int)r.hor_x] == '1')
// 				return (save_color(game, r.hor_dist, r.sy + 2, r.hor_w));
// 			else
// 				r.hor_y += r.sy;
// 		}
// 	}
// }

void	move(t_game *game, int direction)
{
	float	dist;
	float	dx;
	float	dy;
	float	angle;

	angle = game->angle_view + direction * M_PI / 2;
	dx = LINEAR_STEP * cos(angle);
	dy = LINEAR_STEP * sin(angle);
	dist = ray(game, sign(dy) * M_PI / 2);
	if (dist * dist < dy * dy)
		dy = 0.0f;
	dist = ray(game, (1 - (sign(dx) + 1) / 2) * M_PI);
	if (dist * dist < dx * dx)
		dx = 0.0f;
	dist = ray(game, angle);
	if (dist * dist < dy * dy + dx * dx)
		if (sign(dy) * sign(dx) != 0)
			dy = 0.0f;
	game->pos_x += dx;
	game->pos_y -= dy;
}

int	key(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		destroy_exit(game);
	else if (keycode == ARROW_UP || keycode == KEY_W)
		move(game, 0);
	else if (keycode == ARROW_DOWN || keycode == KEY_S)
		move(game, 2);
	else if (keycode == ARROW_LEFT)
		game->angle_view -= ANGLE_STEP * M_PI;
	else if (keycode == ARROW_RIGHT)
		game->angle_view += ANGLE_STEP * M_PI;
	else if (keycode == KEY_A)
		move(game, 3);
	else if (keycode == KEY_D)
		move(game, 1);
	else
		return (0);
	draw(game);
	return (0);
}
