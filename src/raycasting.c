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
	if (r->sx != 0)
	{
		r->vert_y = game->pos_y + r->dy / r->dx * (r->vert_x - game->pos_x);
		r->vert_dist = sqrt(pow(game->pos_x - r->vert_x, 2.0)
				+ pow(game->pos_y - r->vert_y, 2.0));
		r->vert_w = r->vert_y - (int) r->vert_y;
		if (r->sx > 0)
			r->vert_w = 1 - r->vert_w;
	}
	else
		r->vert_dist = INFINITY;
	if (r->sy != 0)
	{
		r->hor_x = game->pos_x + r->dx / r->dy * (r->hor_y - game->pos_y);
		r->hor_dist = sqrt(pow(game->pos_x - r->hor_x, 2.0)
				+ pow(game->pos_y - r->hor_y, 2.0));
		r->hor_w = r->hor_x - (int) r->hor_x;
		if (r->sy < 0)
			r->hor_w = 1 - r->hor_w;
	}
	else
		r->hor_dist = INFINITY;
}

void	ray_initial_calculations(t_game *game, t_ray *r, float v)
{
	r->dx = cos(v);
	r->dy = -sin(v);
	r->sx = sign(r->dx);
	r->sy = sign(r->dy);
	r->vert_x = (int) game->pos_x;
	if (r->sx > 0)
		r->vert_x += 1.0f;
	r->hor_y = (int) game->pos_y;
	if (r->sy > 0)
		r->hor_y += 1.0f;
}
