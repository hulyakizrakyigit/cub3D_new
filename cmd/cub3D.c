#include "cub3D.h"

// char **transpose_map(t_game *game)
// {
//     int i, j;
//     char **new_map;
// 	char *line;

// 	new_map = malloc(sizeof(char *) * (game->pure_map.map_height + 1));

// 	i = 0;
// 	while (i < game->pure_map.map_height)
// 	{
// 		new_map[i] = malloc(sizeof(char) * (game->pure_map.map_width + 1));
// 		if (!new_map[i])
// 		{
// 			perr(__func__, "malloc failed");
// 			return (NULL);
// 		}
// 		j = 0;
// 		while (j < game->pure_map.map_width)
// 		{
// 			if (game->pure_map.map[j])
// 			{
// 			line = game->pure_map.map[j];
// 			if (line && i < (int)ft_strlen(line))
// 				new_map[i][j] = game->pure_map.map[j][i];
// 			}
// 			j++;
// 		}
// 		new_map[i][j] = '\0';
// 		i++;
// 	}
// 	return (new_map);
// }

void	set_player(t_game *game)
{
	int i;
	char c;

	i = 0;
	c = 0;
	while (game->pure_map.map[i])
	{
		if (ft_strchr(game->pure_map.map[i], 'N'))
			c = 'N';
		else if (ft_strchr(game->pure_map.map[i], 'S'))
			c = 'S';
		else if (ft_strchr(game->pure_map.map[i], 'W'))
			c = 'W';
		else if (ft_strchr(game->pure_map.map[i], 'E'))
			c = 'E';
		if (c != 0)
		{
			printf("c : %c\n", c);
			game->map.player.x = i;
			game->map.player.y = ft_strchr(game->pure_map.map[i], c) - game->pure_map.map[i];
			game->map.player.direction = c;
			break ;
		}
		i++;
	}
}

char		**pure_map(char **map, int height)
{
	int i = 0;
	int j = 0;
	char **new_map;
	char *trimmed_line;

	new_map = malloc(sizeof(char *) * (height + 1));
	if (!new_map)
	{
		perr(__func__, "malloc failed");
		return (NULL);
	}
	i = 0;
	 while (map[i])
    {
        trimmed_line = ft_strtrim(map[i], "\n");
        if (trimmed_line && ft_strlen(trimmed_line) > 0) // Boş olmayan satırları kontrol et
        {
            new_map[j++] = trimmed_line;
        }
        else
        {
            free(trimmed_line);
        }
        i++;
    }
    new_map[j] = NULL; // Yeni map dizisini sonlandır

	return (new_map);
}

int main(int ac, char **av)
{
	t_game *game;
	t_err err;

	if (ac != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		return (1);
	}

	game = malloc(sizeof(t_game));
	if (!game)
	{
		perr(__func__, "malloc failed");
		return (1);
	}
	ft_memset(game, 0, sizeof(t_game));
	err = texture_init(&game->map, av[1]);
	if (err != OK)
	{
		perr(__func__, "texture_init failed");
		return (dispose(game), 1);
	}
	err = prepare_map_init(&game->map, av[1]);
	if (err != OK)
	{
		perr(__func__, "map_init failed");
		return (dispose(game), 1);
	}
	err = map_control(&game->map);
	if (err != OK)
	{
		perr(__func__, "map_control failed");
		return (dispose(game), 1);
	}
	err = map_H(&game->map);
	if (err != OK)
	{
		perr(__func__, "map_control_part failed");
		return (dispose(game), 1);
	}
	err = control_player(&game->map);
	if (err != OK)
	{
		perr(__func__, "control_reachable_player failed");
		return (dispose(game), 1);
	}
	err = map_control_part(&game->map);
	if (err != OK)
	{
		perr(__func__, "map_control_part failed");
		return (dispose(game), 1);
	}
	err = validate_map(game->map.map_H);
	if (err != OK)
	{
		perr(__func__, "validate_map failed");
		return (dispose(game), 1);
	}

	// if (init_mlx(game) != OK)
	// {
	// 	perr(__func__, "mlx init failed");
	// 	return (dispose(game), 1);
	// }
	int i;
	i = 0;
	while (game->map.map[i])
	{
		i++;
	}
	game->map.map_height = i;


// game->pure_map.map = (char *[]) {
//     "   1111111111111111111111111",
//     "   1000000000100000000000001",
//     "1011000000100000010000001",
// 	"   ",
//     "1011000000100000010000001",
//     "1011000000100000010000001",
//     "1011000000100000010000001",
//     "101100S000100000010000001",
//     "1011000000100000010000001",
//     "1001000000000011110111111",
//     "1111111110110000011100000001",
//     "100000000011000001110011111111111",
//     "1000000000111101110000001",
//     "11111111111111011101001011111",
//     "11111111110101011100000010001",
//     "10000000000000001100000010001",
//     "10000000000000001101010010001",
//     "11000001110101011111011110011",
//     "11111111 1110101 101111010001",
//     "11111111 1111111 111111111111",
//     NULL
// };
// game->pure_map.map = (char *[]) {
//     "11111111111 111111111111",
//     "1001000000111000000000001111",
//     "111011000001110000000000001",
//     "100100000000000000000000111",
//     "111111111011000001110000000001",
//     "10000000011000001110111111111111",
//     "11110111111111011100000010001",
//     "11110111111111011101010010001",
//     "1000000110101011100010010001",
//     "10000000000000000000001100000010001",
//     "10000000000000011010100100111",
//     "1100001110101011111011111N1111",
//     "11110111 111011 10111010101",
//     "1111111 111111 111111111111",
//     NULL
// };
i = 0;

game->pure_map.map = pure_map(game->map.map, game->map.map_height);
game->pure_map.map_height = game->map.map_height;
game->pure_map.map_width = game->map.map_width;

// char **map = transpose_map(game);
// i = 0;
// while (map[i])
// {
// 	printf("%s\n", map[i]);
// 	i++;
// }

set_player(game);
i = 0;
while (game->pure_map.map[i])
{
	printf("%s\n", game->pure_map.map[i]);
	i++;
}

	start_game(game);

// 	mlx_hook(game->win_ptr, 17, 0, close_window, game); //çarpı işaretinden kapanacak
//    // mlx_key_hook(game->win_ptr, esc_press, game); //esc ile kapancak
// 	if (image_up(game) != OK)
// 	{
// 		perr(__func__, "image up failed");
// 		return (dispose(game), 1);
// 	}
// 	mlx_loop_hook(game->mlx.mlx, start_game, game);
// 	mlx_loop(game->mlx);
	return (dispose(game), 0);
}

