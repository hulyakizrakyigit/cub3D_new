#include "cub3D.h"
#include <math.h>


void	draw(t_game *game)
{
	game->img_w.img = mlx_new_image(game->mlx.mlx, WIDTH, HEIGHT);
	game->img_w.addr = mlx_get_data_addr(game->img_w.img, &game->img_w.bpp,
			&game->img_w.line_length, &game->img_w.endian);
	draw_ceiling_and_floor(game);
	ray_casting(game);
	mlx_put_image_to_window(game->mlx.mlx,
		game->mlx.win, game->img_w.img, 0, 0);
	mlx_destroy_image(game->mlx.mlx, game->img_w.img);
}

void resoures_initialisation(t_game *game)
{
    load_textures(game);
    load_textures_addresses(game);
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

void	set_position(t_game *game)
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
	game->color_ceiling = game->map.texture.C.R << 16
		| game->map.texture.C.G << 8 | game->map.texture.C.B;
	game->color_floor = game->map.texture.F.R << 16
		| game->map.texture.F.G << 8 | game->map.texture.F.B;
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
