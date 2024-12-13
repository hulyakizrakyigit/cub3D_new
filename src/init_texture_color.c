#include "cub3D.h"

static void ft_free_all(char **arr, int i)
{
    while (i >= 0)
    {
        free(arr[i]);
        i--;
    }
    free(arr);
}

// Yardımcı fonksiyon: Kelime uzunluğunu hesaplar
static int ft_word_len(const char *s, char c)
{
    int len = 0;
    while (s[len] && s[len] != c)
        len++;
    return (len);
}

// Ana fonksiyon: ft_split
char **ft_split_a(const char *s, char c)
{
    char    **arr;
    int     i = 0, j;
    int     word_count = 0, word_len;

    if (!s)
        return (NULL);
    // Kelime sayısını hesapla
    for (j = 0; s[j]; j++)
        if ((s[j] != c && (j == 0 || s[j - 1] == c)))
            word_count++;
    // Bellek tahsisi
    arr = (char **)malloc(sizeof(char *) * (word_count + 1));
    if (!arr)
        return (NULL);
    // Diziyi doldur
    j = 0;
    while (i < word_count)
      {
        while (s[j] == c)
            j++;
        word_len = ft_word_len(&s[j], c);
        arr[i] = (char *)malloc(sizeof(char) * (word_len + 1));
        if (!arr[i])
        {
            ft_free_all(arr, i - 1);
            return (NULL);
        }
        for (int k = 0; k < word_len; k++)
            arr[i][k] = s[j + k];
        arr[i][word_len] = '\0';
        j += word_len;
        i++;
    }
    arr[word_count] = NULL;
    return (arr);
}

t_err	control_texture_color(t_color *color)
{
	if (color->R < 0 || color->R > 255)
		return (perr(__func__, "Invalid color R"));
	if (color->G < 0 || color->G > 255)
		return (perr(__func__, "Invalid color G"));
	if (color->B < 0 || color->B > 255)
		return (perr(__func__, "Invalid color B"));
	if (color->count != 1)
		return (perr(__func__, "Invalid color count."));
	return (OK);
}

t_err	is_invalid_color(char **rgb_str_arr)
{
	int		i;
	char	*tmp;

	i = 0;
	while (rgb_str_arr[i])
	{
		tmp = ft_strtrim(rgb_str_arr[i], "\t\v\f\r\n ");
		if (!tmp || !strevery(&ft_isdigit, tmp) || tmp[0] == '\0')
		{
			free(tmp);
			return (perr(__func__, "Invalid color, not digit"));
		}
		free(rgb_str_arr[i]);
		rgb_str_arr[i] = tmp;
		i++;
	}
	if (i != 3)
	{
		return (perr(__func__, "Invalid rgb count, must be 3"));
	}
	return (OK);
}

t_err	check_texture_color(char *line, t_map *map)
{
	if (!line)
		return (ERR);
	if (!ft_strncmp(line, "F ", 2))
	{
		map->texture.F.rgb_str = ft_strtrim_a(line + 2, " ");
		map->texture.F.rgb_str_arr = ft_split(map->texture.F.rgb_str, ',');
		free(map->texture.F.rgb_str);
		if (!is_invalid_color(map->texture.F.rgb_str_arr))
		{
			return (ERR);
		}
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		map->texture.C.rgb_str = ft_strtrim_a(line + 2, " ");
		map->texture.C.rgb_str_arr = ft_split(map->texture.C.rgb_str, ',');
		free(map->texture.C.rgb_str);
		if (!is_invalid_color(map->texture.C.rgb_str_arr))
		{
			return (ERR);
		}
	}
	return (OK);
}
