#include "cub3D.h"
#include <fcntl.h>

void load_textures(t_game *game)
{
    game->txt[0].img = mlx_xpm_file_to_image(game->mlx.mlx,
		game->map.texture.EA.path, &game->txt[0].width, &game->txt[0].height);
    game->txt[1].img = mlx_xpm_file_to_image(game->mlx.mlx,
		game->map.texture.NO.path, &game->txt[1].width, &game->txt[1].height);
    game->txt[2].img = mlx_xpm_file_to_image(game->mlx.mlx,
		game->map.texture.SO.path, &game->txt[2].width, &game->txt[2].height);
    game->txt[3].img = mlx_xpm_file_to_image(game->mlx.mlx,
		game->map.texture.WE.path, &game->txt[3].width, &game->txt[3].height);
    if (!game->txt[0].img || !game->txt[1].img || !game->txt[2].img
		|| !game->txt[3].img)
    {
        printf("Error\nmlx_xpm_file_to_image failed\n");
        exit(0);
    }
}

void load_textures_addresses(t_game *game)
{
    game->txt[0].addr = mlx_get_data_addr(game->txt[0].img,
		&game->txt[0].bpp, &game->txt[0].line_length, &game->txt[0].endian);
    game->txt[1].addr = mlx_get_data_addr(game->txt[1].img,
		&game->txt[1].bpp, &game->txt[1].line_length, &game->txt[1].endian);
    game->txt[2].addr = mlx_get_data_addr(game->txt[2].img,
		&game->txt[2].bpp, &game->txt[2].line_length, &game->txt[2].endian);
    game->txt[3].addr = mlx_get_data_addr(game->txt[3].img,
		&game->txt[3].bpp, &game->txt[3].line_length, &game->txt[3].endian);
	if (!game->txt[0].addr || !game->txt[1].addr || !game->txt[2].addr
		|| !game->txt[3].addr)
    {
        printf("Error\nmlx_get_data_addr failed\n");
        exit(0);
    }
}

static void	control_textures(t_texture *texture)
{
	control_texture_dir(texture);
	control_texture_color(&texture->C);
	control_texture_color(&texture->F);
}

static bool	handle_empty_line(char *line, t_map *map)
{
	if (is_empty_line(line) && (ft_strlen(line) == 1)
		&& !(map->texture.NO.count == 1 && map->texture.SO.count == 1
		&& map->texture.WE.count == 1 && map->texture.EA.count == 1
		&& map->texture.F.count == 1 && map->texture.C.count == 1))
	{
		map->map_len++;
		map->row++;
		free(line);
		return (true);
	}
	return (false);
}

t_err	texture_init(t_map *map, char *path)
{
	int		fd;
	char	*line;
	t_err	err;

	if (!map || !path)
		return (perr(__func__, "unexpected error"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perr(__func__, "open failed"));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (handle_empty_line(line, map))
			continue ;
		err = set_texture(line, map);
		if (err != OK)
			return (free(line), close(fd), err);
		free(line);
		map->map_len++;
	}
	control_textures(&map->texture);
	return (close(fd), OK);
}

