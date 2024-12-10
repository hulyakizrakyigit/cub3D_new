#include "cub3D.h"
#include <math.h>

int	destroy_exit(t_game *game)
{
	dispose(game);
	exit(0);
}

float ray_check_horizontal(t_game *game, t_ray *r)
{
    int index_y = (int)r->hor_y + (r->sy - 1) / 2;

    if ((int)r->hor_x < 0 || (int)r->hor_x >= game->pure_map.map_width - 1)
        return (INFINITY);
    if (index_y < 0 || index_y >= game->pure_map.map_height - 1)
        return (INFINITY);
    if (game->pure_map.map[index_y][(int)r->hor_x] == '1')
        return (save_color(game, r->hor_dist, r->sy + 2, r->hor_w));
    else
        r->hor_y += r->sy;

    return OK;
}

float ray_check_vertical(t_game *game, t_ray *r)
{
    int index_x = (int)r->vert_x + (r->sx - 1) / 2;

    if (index_x < 0 || index_x >= game->pure_map.map_width - 1)
        return (INFINITY);
    if ((int)r->vert_y < 0 || (int)r->vert_y >= game->pure_map.map_height - 1)
        return (INFINITY);
    if (game->pure_map.map[(int)r->vert_y][index_x] == '1')
        return (save_color(game, r->vert_dist, r->sx + 1, r->vert_w));
    else
        r->vert_x += r->sx;

    return OK;
}

float ray_next_steps_part(t_game *game, t_ray *r)
{
    while (1)
    {
        ray_next_step_calculation(game, r);

        if (r->vert_dist < r->hor_dist)
        {
            float result = ray_check_vertical(game, r);
            if (result != OK)
                return result;
        }
        else
        {
            float result = ray_check_horizontal(game, r);
            if (result != OK)
                return result;
        }
    }
}


float ray_initial_part(t_game *game, float v, t_ray *r)
{
    ray_initial_calculations(game, r, v);
    return OK;
}

float ray(t_game *game, float v)
{
    t_ray r;
    t_err err;

    err = ray_initial_part(game, v, &r);
    if (err != OK)
        return INFINITY;

    return ray_next_steps_part(game, &r);
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
