/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:00:27 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/24 15:07:08 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	grid_free(char **grid, int h)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (i < h)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

char	**grid_dup(char **src, int h)
{
	char	**dst;
	int		i;

	dst = malloc ((h + 1) * sizeof(char *));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < h)
	{		
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
			return (grid_free(dst, i), (NULL));
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

static void	fill(char **grid, int h, int w, int y, int x)
{
	if (y < 0 || y >= h || x < 0 || x >= w)
		return ;
	if (grid[y][x] == '1' || grid[y][x] == 'V' || grid[y][x] == 'F')
		return ;
	grid[y][x] = 'F';
	fill(grid, h, w, y - 1, x);
	fill(grid, h, w, y + 1, x);
	fill(grid, h, w, y, x - 1);
	fill(grid, h, w, y, x + 1);
}

int	is_path_solvable(t_game *game)
{
	char	**tmp;
	int		y;
	int		x;

	tmp = grid_dup(game->map->grid, game->map->height);
	if (!tmp)
		return (0);
	fill(tmp, game->map->height, game->map->width, game->py, game->px);
	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (tmp[y][x] == 'C' || tmp[y][x] == 'E')
				return (grid_free(tmp, game->map->height), 0);
			x++;
		}
		y++;
	}
	grid_free(tmp, game->map->height);
	return (1);
}
