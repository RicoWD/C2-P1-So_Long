/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:43:47 by ubuntu            #+#    #+#             */
/*   Updated: 2025/07/02 04:34:00 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// void	grid_free(char **grid, int height)
// {
// 	int	i;

// 	if (!grid)
// 		return ;
// 	i = 0;
// 	while (i < height && grid[i])
// 	{
// 		free(grid[i]);
// 		i++;
// 	}
// 	free(grid);
// }

void	destroy_level(t_game *g)
{
	int	i;

	i = 0;
	while (i < NB_TEX)
	{
		if (g->tex[i])
		{
			mlx_destroy_image(g->mlx, g->tex[i]);
			g->tex[i] = NULL;
		}
		i++;
	}
}

void    destroy_game(t_game *g)
{
    int i;

    i = 0;
    while (i < NB_TEX)
    {
        if (g->tex[i])
            mlx_destroy_image(g->mlx, g->tex[i]);
        i++;
    }
    if (g->win)
        mlx_destroy_window(g->mlx, g->win);
    if (g->map && g->map->grid)
        grid_free(g->map->grid);
    mlx_destroy_display(g->mlx);
    free(g->mlx);
}

int	close_window(t_game *g)
{
	destroy_game(g);
	exit(EXIT_SUCCESS);
}