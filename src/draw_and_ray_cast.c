#include "cub3D.h"

void	line(t_game *game, int w, float dist)
{
	unsigned int	*dst;
	unsigned int	*src;
	unsigned int	h;
	float			src_f;
	float			d_shift;

	h = (float) HEIGHT / dist + 0.5f;
	src_f = 0.0f;
	d_shift = (float) game->txt[game->txt_idx].height / h;
	if (h > HEIGHT)
	{
		src_f = 0.5f * (h - HEIGHT) / h * game->txt[game->txt_idx].height;
		h = HEIGHT;
	}
	src = (unsigned int *) game->txt[game->txt_idx].addr;
	src += (int)((float) game->txt_w * game->txt[game->txt_idx].width);
	dst = (unsigned int *) game->img_w.addr + w + (HEIGHT - h) / 2 * WIDTH;
	while (h-- > 0)
	{
		*dst = *(src + ((int)src_f) * game->txt[game->txt_idx].width);
		dst += WIDTH;
		src_f += d_shift;
	}
}

void	ray_casting(t_game *game)
{
	int		x;
	float	dv;
	float	v;
	float	ray_r;

	v = game->angle_view - FOV / 2;
	dv = FOV / (WIDTH - 1);
	x = -1;
	while (++x < WIDTH)
	{
		ray_r = ray(game, v);
		if (ray_r == INFINITY)
			ray_r = 0.1f;
		if (ray_r < 0.1f)
			ray_r = 0.1f;
		line(game, x, ray_r * cos(game->angle_view - v));
		v += dv;
	}
}

void	draw_ceiling_and_floor(t_game *game)
{
	unsigned int	*dst;
	unsigned int	i;

	dst = (unsigned int *) game->img_w.addr;
	i = WIDTH * HEIGHT / 2 + 1;
	while (--i > 0)
		*dst++ = game->color_ceiling;
	i = WIDTH * HEIGHT / 2 + 1;
	while (--i > 0)
		*dst++ = game->color_floor;
}
