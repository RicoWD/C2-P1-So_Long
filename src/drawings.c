/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 02:13:16 by ubuntu            #+#    #+#             */
/*   Updated: 2025/07/01 05:51:18 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_bg(t_game *g, t_tex id)
{
	int		y;
	int		x;

	y = 0;
	(void)id;
	while (y < g->map->height * TILE)
	{
		x = 0;
		while (x < g->map->width * TILE)
		{
			map_displayer(g, x, y, id);
			x++;
		}
		y++;
	}
}

void	draw_map(t_game *g, char *line, int y)
{
	int		x;

	x = 0;
	while (x < g->map->width)
	{
		map_displayer(g, x, y, TEX_FLOOR);
		if (line[x] == '1')
			map_displayer(g, x, y, TEX_WALL);
		else if (line[x] == 'E')
			map_displayer(g, x, y, TEX_EXIT);
		else if (line[x] == 'V')
			map_displayer(g, x, y, TEX_VILAIN);
		x++;
	}
}

void	draw_collect(t_game *g, char *line, int y)
{
	int		x;

	x = 0;
	while (x < g->map->width)
	{
		if (line[x] == 'C')
			map_displayer(g, x, y, TEX_COLLECT);
		x++;
	}
}

void	draw_player(t_game *g, char *line, int y)
{
	int		x;

	x = 0;
	while (x < g->map->width)
	{
		if (line[x] == 'P')
			map_displayer(g, x, y, TEX_PLAYER_FRONT);
		x++;
	}
}
