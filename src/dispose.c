#include "cub3D.h"

void	strr_arr_dispose(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}


void dispose(t_game *game)
{
    if (game->last_map.map_H)
    {
        strr_arr_dispose(game->last_map.map_H);
        game->last_map.map_H = NULL;
    }
    if (game->pure_map.map)
    {
        strr_arr_dispose(game->pure_map.map);
        game->pure_map.map = NULL;
    }
    if (game->map.map)
    {
        strr_arr_dispose(game->map.map);
        game->map.map = NULL;
    }
    if (game->mlx.win)
    {
        mlx_destroy_window(game->mlx.mlx, game->mlx.win);
        game->mlx.win = NULL;
    }
    if (game->mlx.mlx)
    {
        free(game->mlx.mlx);
        game->mlx.mlx = NULL;
    }
    if (game->map.texture.F.rgb_str_arr)
    {
        for (int i = 0; i < 3; i++)
        {
            free(game->map.texture.F.rgb_str_arr[i]);
        }
        free(game->map.texture.F.rgb_str_arr);
        game->map.texture.F.rgb_str_arr = NULL;
    }
    if (game->map.texture.C.rgb_str_arr)
    {
        for (int i = 0; i < 3; i++)
        {
            free(game->map.texture.C.rgb_str_arr[i]);
        }
        free(game->map.texture.C.rgb_str_arr);
        game->map.texture.C.rgb_str_arr = NULL;
    }
}


// void dispose(t_game *game)
// {
//     if (game->last_map.map_H)
//     {
//         strr_arr_dispose(game->last_map.map_H);
//         game->last_map.map_H = NULL;
//     }
//     if (game->pure_map.map)
//     {
//         int i = 0;
//         while (game->pure_map.map[i])
//         {
//             free(game->pure_map.map[i]);
//             i++;
//         }
//         free(game->pure_map.map);
//         game->pure_map.map = NULL;
//     }
//     if (game->map.map)
//     {
//         int i = 0;
//         while (game->map.map[i])
//         {
//             free(game->map.map[i]);
//             i++;
//         }
//         free(game->map.map);
//         game->map.map = NULL;
//     }
//     if (game->mlx.win)
//     {
//         mlx_destroy_window(game->mlx.mlx, game->mlx.win);
//         game->mlx.win = NULL;
//     }
//     if (game->mlx.mlx)
//     {
//         free(game->mlx.mlx);
//         game->mlx.mlx = NULL;
//     }
// }

