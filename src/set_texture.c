/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:47:45 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 21:56:52 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_err	control_texture_dir(t_texture *texture)
{
	if (texture->no.count != 1)
		return (perr(__func__, "Invalid texture NO count."));
	if (texture->so.count != 1)
		return (perr(__func__, "Invalid texture SO count."));
	if (texture->we.count != 1)
		return (perr(__func__, "Invalid texture WE count."));
	if (texture->ea.count != 1)
		return (perr(__func__, "Invalid texture EAcount."));
	return (OK);
}

t_err	set_texture(char *line, t_map *map)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		set_texture_dir(line, map);
	if (!ft_strncmp(line, "F ", 2))
	{
		if (!check_texture_color(line, map))
			return (ERR);
		set_texture_color_f(&map->texture);
		map->row++;
	}
	if (!ft_strncmp(line, "C ", 2))
	{
		if (!check_texture_color(line, map))
			return (ERR);
		set_texture_color_c(&map->texture);
		map->row++;
	}
	return (OK);
}

void	set_texture_for_direction(char *line, t_map *map, t_img *texture)
{
	char	*tmp;

	if (!line || !texture)
		return ;
	texture->path = ft_strdup(line + 3);
	tmp = ft_strtrim_a(line + 3, "\t\v\f\r\n ");
	if (!tmp)
		return ;
	if (texture->path)
	{
		free(texture->path);
		texture->path = NULL;
	}
	texture->path = tmp;
	texture->count++;
	map->row++;
}

void	set_texture_dir(char *line, t_map *map)
{
	if (!line)
		return ;
	if (ft_strncmp(line, "NO ", 3) == 0)
		set_texture_for_direction(line, map, &map->texture.no);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		set_texture_for_direction(line, map, &map->texture.so);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		set_texture_for_direction(line, map, &map->texture.we);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		set_texture_for_direction(line, map, &map->texture.ea);
}
