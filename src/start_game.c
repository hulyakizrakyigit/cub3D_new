#include "cub3D.h"
#include <math.h>

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

void	draw(t_game *game)
{
	game->img_w.img = mlx_new_image(game->mlx.mlx, WIDTH, HEIGHT);
	game->img_w.addr = mlx_get_data_addr(game->img_w.img, &game->img_w.bpp,
			&game->img_w.line_length, &game->img_w.endian);
	draw_ceiling_and_floor(game);
	ray_casting(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->img_w.img, 0, 0);
	mlx_destroy_image(game->mlx.mlx, game->img_w.img);
}



void	resoures_initialisation(t_game *game)
{
	game->txt[0].img = mlx_xpm_file_to_image(game->mlx.mlx, game->map.texture.EA.path, &game->txt[0].width, &game->txt[0].height);
	game->txt[1].img = mlx_xpm_file_to_image(game->mlx.mlx, game->map.texture.NO.path, &game->txt[1].width, &game->txt[1].height);
	game->txt[2].img = mlx_xpm_file_to_image(game->mlx.mlx, game->map.texture.SO.path, &game->txt[2].width, &game->txt[2].height);
	game->txt[3].img = mlx_xpm_file_to_image(game->mlx.mlx, game->map.texture.WE.path, &game->txt[3].width, &game->txt[3].height);

	if (!game->txt[0].img || !game->txt[1].img || !game->txt[2].img || !game->txt[3].img)
	{
		printf("Error\nmlx_xpm_file_to_image failed\n");
		exit(0);
	}
	game->txt[0].addr = mlx_get_data_addr(game->txt[0].img,
			&game->txt[0].bpp, &game->txt[0].line_length,
			&game->txt[0].endian);
	game->txt[1].addr = mlx_get_data_addr(game->txt[1].img, &game->txt[1].bpp,
			&game->txt[1].line_length, &game->txt[1].endian);
	game->txt[2].addr = mlx_get_data_addr(game->txt[2].img, &game->txt[2].bpp,
			&game->txt[2].line_length, &game->txt[2].endian);
	game->txt[3].addr = mlx_get_data_addr(game->txt[3].img, &game->txt[3].bpp,
			&game->txt[3].line_length, &game->txt[3].endian);

	if (!game->txt[0].addr || !game->txt[1].addr || !game->txt[2].addr || !game->txt[3].addr)
	{
		printf("Error\nmlx_get_data_addr failed\n");
		exit(0);
	}
}

void	set_angle_view(t_game *game)
{
	if (game->map.player.direction == 'N')
		game->angle_view = 0.5f * M_PI;
	else if (game->map.player.direction == 'E')
		game->angle_view = 0.0f * M_PI;
	else if (game->map.player.direction == 'S')
		game->angle_view = -0.5f * M_PI;
	else if (game->map.player.direction == 'W')
		game->angle_view = 1.0f * M_PI;
}
void set_position(t_game *game)
{
	game->pos_y = game->map.player.x +0.5f;
	game->pos_x = game->map.player.y +0.5f;
		if (game->map.player.direction == 'N')
		game->pos_y -= 0.2f;
	else if (game->map.player.direction == 'S')
		game->pos_y += 0.2f;
	else if (game->map.player.direction == 'W')
		game->pos_x -= 0.2f;
	else if (game->map.player.direction == 'E')
		game->pos_x += 0.2f;
	set_angle_view(game);
}

void	start_game(t_game *game)
{
	game->color_ceiling = game->map.texture.C.R << 16 | game->map.texture.C.G << 8 | game->map.texture.C.B;
	game->color_floor = game->map.texture.F.R << 16 | game->map.texture.F.G << 8 | game->map.texture.F.B;
	set_position(game);
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
	{
		printf("Error\nmlx init failed\n");
		exit(0);
	}
	resoures_initialisation(game);
	game->mlx.win = mlx_new_window(game->mlx.mlx, WIDTH, HEIGHT, "cub3D");
	draw(game);
	mlx_hook(game->mlx.win, ON_KEYDOWN, KeyPressMask, key, game);
	mlx_hook(game->mlx.win, ON_DESTROY, NoEventMask, destroy_exit, game);
	mlx_loop(game->mlx.mlx);
}
