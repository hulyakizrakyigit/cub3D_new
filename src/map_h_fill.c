#include "cub3D.h"

t_err map_H_fill(t_map *map)
{
    int i;
    int j;

    i = 0;
    while (i < map->map_len - map->row)
    {
        j = 0;
        while (map->map[i][j] != '\0')
        {
            if (map->map[i][j] == ' ' || map->map[i][j] == '\t' || map->map[i][j] == '\v'
            || map->map[i][j] == '\f' || map->map[i][j] == '\r' || map->map[i][j] == '\n')
                map->map_H[i][j] = 'H';
            else
                map->map_H[i][j] = map->map[i][j];
            j++;
        }
        i++;
    }
    return OK;
}

t_err allocate_map_H(t_map *map)
{
    int i;

    i = 0;
    map->map_H = malloc(sizeof(char *) * (map->map_len - map->row + 2));
    if (!map->map_H)
        return (perr(__func__, "malloc failed(map_H)"));
    while (i < map->map_len - map->row)
    {
        map->map_H[i] = malloc(sizeof(char) * (map->map_width + 1));
        if (!map->map_H[i])
            return (strr_arr_dispose(map->map_H), perr(__func__, "malloc failed(map_H row)"));
        ft_memset(map->map_H[i], 'H', map->map_width);
        map->map_H[i][map->map_width] = '\0';
        i++;
    }
    map->map_H[i] = NULL;
    return OK;
}


t_err map_H(t_map *map)
{
    t_err err;

    map->map_width = map_width(map);
    err = allocate_map_H(map);
    if (err != OK)
        return err;
    err = map_H_fill(map);
    if (err != OK)
        strr_arr_dispose(map->map_H);
    return (OK);
}
