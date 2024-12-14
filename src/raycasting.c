#include "cub3D.h"
#include <math.h>

int	sign(float f)
{
	if (f < 0.0f)
	{
		if (f > -0.000001)
			return (0);
		else
			return (-1);
	}
	else
	{
		if (f < 0.000001f)
			return (0);
		else
			return (1);
	}
}

float	save_color(t_game *game, float dist, int color_idx, float w)
{
	game->txt_idx = color_idx;
	game->txt_w = w;
	return (dist);
}

void	ray_next_step_calculation(t_game *game, t_ray *r)
{
	if (r->step_x != 0)
	{
		r->vertical_y = game->pos_y + r->delta_y / r->delta_x * (r->vertical_x - game->pos_x);
		r->vertical_distance = sqrt(pow(game->pos_x - r->vertical_x, 2.0) + pow(game->pos_y
					- r->vertical_y, 2.0));
		r->vertical_weight = r->vertical_y - (int)r->vertical_y;
		if (r->step_x > 0)
			r->vertical_weight = 1 - r->vertical_weight;
	}
	else
		r->vertical_distance = INFINITY;
	if (r->step_y != 0)
	{
		r->horizontal_x = game->pos_x + r->delta_x / r->delta_y * (r->horizontal_y - game->pos_y);
		r->horizontal_distance = sqrt(pow(game->pos_x - r->horizontal_x, 2.0) + pow(game->pos_y
					- r->horizontal_y, 2.0));
		r->horizontal_weight = r->horizontal_x - (int)r->horizontal_x;
		if (r->step_y < 0)
			r->horizontal_weight = 1 - r->horizontal_weight;
	}
	else
		r->horizontal_distance = INFINITY;
}

