/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:00:27 by erpascua          #+#    #+#             */
/*   Updated: 2025/07/01 05:56:52 by ubuntu           ###   ########.fr       */
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

static void	fill(char **grid, t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return ;
	if (grid[y][x] == '1' || grid[y][x] == 'V' || grid[y][x] == 'F')
		return ;
	grid[y][x] = 'F';
	fill(grid, map, y - 1, x);
	fill(grid, map, y + 1, x);
	fill(grid, map, y, x - 1);
	fill(grid, map, y, x + 1);
}

int	is_path_solvable(t_game *g)
{
	char	**tmp;
	int		y;
	int		x;

	tmp = grid_dup(g->map->grid, g->map->height);
	if (!tmp)
		return (0);
	fill(tmp, g->map, g->py, g->px);
	y = 0;
	while (y < g->map->height)
	{
		x = 0;
		while (x < g->map->width)
		{
			if (tmp[y][x] == 'C' || tmp[y][x] == 'E')
				return (grid_free(tmp, g->map->height), 0);
			x++;
		}
		y++;
	}
	grid_free(tmp, g->map->height);
	return (1);
}
