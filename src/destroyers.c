/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:43:47 by ubuntu            #+#    #+#             */
/*   Updated: 2025/07/03 20:43:40 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_all(t_game *g)
{
	if (!g)
		return ;
	if (g->map && g->map->grid)
		grid_free(g->map->grid);
}

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

void	destroy_game(t_game *g)
{
	int	i;

	i = 0;
	if (!g || !g->mlx)
		return ;
	while (i < NB_TEX)
	{
		if (g->tex[i])
		{
			mlx_destroy_image(g->mlx, g->tex[i]);
			g->tex[i] = NULL;
		}
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
