#include "cub3D.h"

float	ray_check_horizontal(t_game *game, t_ray *r)
{
	int	index_y;

	index_y = (int)r->hor_y + (r->sy - 1) / 2;
	if ((int)r->hor_x < 0 || (int)r->hor_x >= game->pure_map.map_width - 1)
		return (INFINITY);
	if (index_y < 0 || index_y >= game->pure_map.map_height - 1)
		return (INFINITY);
	if (game->pure_map.map[index_y][(int)r->hor_x] == '1')
		return (save_color(game, r->hor_dist, r->sy + 2, r->hor_w));
	else
		r->hor_y += r->sy;
	return (OK);
}

float	ray_check_vertical(t_game *game, t_ray *r)
{
	int	index_x;

	index_x = (int)r->vert_x + (r->sx - 1) / 2;
	if (index_x < 0 || index_x >= game->pure_map.map_width - 1)
		return (INFINITY);
	if ((int)r->vert_y < 0 || (int)r->vert_y >= game->pure_map.map_height - 1)
		return (INFINITY);
	if (game->pure_map.map[(int)r->vert_y][index_x] == '1')
		return (save_color(game, r->vert_dist, r->sx + 1, r->vert_w));
	else
		r->vert_x += r->sx;
	return (OK);
}

float	ray_next_steps_part(t_game *game, t_ray *r)
{
	float	result;

	while (1)
	{
		ray_next_step_calculation(game, r);
		if (r->vert_dist < r->hor_dist)
		{
			result = ray_check_vertical(game, r);
			if (result != OK)
				return (result);
		}
		else
		{
			result = ray_check_horizontal(game, r);
			if (result != OK)
				return (result);
		}
	}
}

float	ray_initial_part(t_game *game, float v, t_ray *r)
{
	ray_initial_calculations(game, r, v);
	return (OK);
}
