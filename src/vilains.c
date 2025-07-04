/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vilains.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:18:00 by ubuntu            #+#    #+#             */
/*   Updated: 2025/07/04 00:48:15 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "so_long.h"

void	enemy_init(t_game *g)
{
	int	y;
	int	x;

	g->nb_vilains = 0;
	y = 0;
	while (y < g->map->height)
	{
		x = 0;
		while (x < g->map->width)
		{
			if (g->map->grid[y][x] == 'V' && g->nb_vilains < 9)
			{
				g->s_vilain[g->nb_vilains].x = x;
				g->s_vilain[g->nb_vilains].y = y;
				g->s_vilain[g->nb_vilains].dir = 1;
				g->s_vilain[g->nb_vilains].axis = 0;
				g->s_vilain[g->nb_vilains].frame = 0;
				g->nb_vilains++;
			}
			x++;
		}
		y++;
	}
}

int	update_loop(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->nb_vilains)
	{
		t_vilain *e = &g->s_vilain[i];
		if (++e->frame < 10)
		{
			i++;
			continue;
		}
		e->frame = 0;
		int nx = e->x + (e->axis == 0) * e->dir;
		int ny = e->y + (e->axis == 1) * e->dir;
		if (g->map->grid[ny][nx] == '1')
			e->dir = -e->dir;
		else
		{
			map_displayer(g, e->x, e->y, TEX_FLOOR);
			e->x = nx;
			e->y = ny;
			map_displayer(g, e->x, e->y, TEX_VILAIN);
		}
		i++;
	}
	return (0);
}