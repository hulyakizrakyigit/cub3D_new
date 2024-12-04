#include "cub3D.h"

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
	int i;
	i = 0;
	while (game->map.map[i])
	{
		i++;
	}
	game->map.map_height = i;

game->pure_map.map = pure_map(game->map.map, game->map.map_height);
game->pure_map.map_height = game->map.map_height;
game->pure_map.map_width = game->map.map_width;


set_player(game);
i = 0;
while (game->pure_map.map[i])
{
	printf("%s\n", game->pure_map.map[i]);
	i++;
}
	start_game(game);
	return (dispose(game), 0);
}

