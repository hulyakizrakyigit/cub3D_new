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

void	dispose(t_game *game)
{
	free(game);
}
