#include "cub3D.h"
#include <math.h>

float	ray(t_game *game, float v)
{
	t_ray	r;
	t_err	err;

	err = ray_initial_part(game, v, &r);
	if (err != OK)
		return (INFINITY);
	return (ray_next_steps_part(game, &r));
}

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
