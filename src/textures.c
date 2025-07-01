/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 01:56:41 by ubuntu            #+#    #+#             */
/*   Updated: 2025/07/01 08:29:32 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	textures_init(t_game *g)
{
	load_tex(g, TEX_WALL, "textures/wall.xpm");
	load_tex(g, TEX_FLOOR, "textures/floor.xpm");
	load_tex(g, TEX_PLAYER, "textures/player.xpm");
	load_tex(g, TEX_PLAYER_LEFT, "textures/player_left.xpm");
	load_tex(g, TEX_PLAYER_RIGHT, "textures/player_right.xpm");
	load_tex(g, TEX_PLAYER_FRONT, "textures/player_front.xpm");
	load_tex(g, TEX_PLAYER_BACK, "textures/player_back.xpm");
	load_tex(g, TEX_COLLECT, "textures/collect.xpm");
	load_tex(g, TEX_EXIT, "textures/exit.xpm");
	load_tex(g, TEX_VILAIN, "textures/vilain.xpm");
	load_tex(g, ATH_TEX_BG, "textures/ath_bg.xpm");
	load_tex(g, ATH_TEX_LIFE, "textures/ath_life.xpm");
	load_tex(g, ATH_TEX_COLLECT, "textures/ath_collect.xpm");
	load_tex(g, ATH_TEX_MOVE, "textures/ath_moves.xpm");
	load_tex(g, ATH_TEX_PLAYER, "textures/ath_player.xpm");
	load_tex(g, TEX_0, "textures/alphanum/0.xpm");
	load_tex(g, TEX_1, "textures/alphanum/1.xpm");
	load_tex(g, TEX_2, "textures/alphanum/2.xpm");
	load_tex(g, TEX_3, "textures/alphanum/3.xpm");
	load_tex(g, TEX_4, "textures/alphanum/4.xpm");
	load_tex(g, TEX_5, "textures/alphanum/5.xpm");
	load_tex(g, TEX_6, "textures/alphanum/6.xpm");
	load_tex(g, TEX_7, "textures/alphanum/7.xpm");
	load_tex(g, TEX_8, "textures/alphanum/8.xpm");
	load_tex(g, TEX_9, "textures/alphanum/9.xpm");
}

void	draw_ath(t_game *g, char *row)
{
	int	y;
	int	x;

	y = g->map->height;
	x = 0;
	while (x < g->win_w)
		map_displayer(g, x++, y, ATH_TEX_BG);
	x = 0;
	while (row[x] && x < g->win_w)
	{
		draw_map_per_pxl(g, row, &x, y);
		x++;
	}
}

static int	draw_number(t_game *g, int nb, int x, int y)
{
	char	*s;
	int		i;

	s = ft_itoa(nb);
	i = 0;
	while (s[i] && x + i < g->win_w)
	{
		num_to_xpm(g, s[i] - '0', x + i, y);
		i++;
	}
	free(s);
	return (i);
}

void	draw_map_per_pxl(t_game *g, char *row, int *x, int y)
{
	if (row[*x] == 'S')
		map_displayer(g, *x, y, ATH_TEX_BG);
	else if (row[*x] == 'h')
		*x += draw_number(g, g->remaining_p_life, *x, y) - 1;
	else if (row[*x] == 'H')
		map_displayer(g, *x, y, ATH_TEX_LIFE);
	else if (row[*x] == 'P')
		map_displayer(g, *x, y, ATH_TEX_PLAYER);
	else if (row[*x] == 'c')
		*x += draw_number(g, g->map->remaining_c, *x, y) - 1;
	else if (row[*x] == 'C')
		map_displayer(g, *x, y, ATH_TEX_COLLECT);
	else if (row[*x] == 'm')
		*x += draw_number(g, g->moves, *x, y) - 1;
	else if (row[*x] == 'M')
		map_displayer(g, *x, y, ATH_TEX_MOVE);
}

void	num_to_xpm(t_game *g, int nb, int x, int y)
{
	if (nb == 0)
		map_displayer(g, x, y, TEX_0);
	else if (nb == 1)
		map_displayer(g, x, y, TEX_1);
	else if (nb == 2)
		map_displayer(g, x, y, TEX_2);
	else if (nb == 3)
		map_displayer(g, x, y, TEX_3);
	else if (nb == 4)
		map_displayer(g, x, y, TEX_4);
	else if (nb == 5)
		map_displayer(g, x, y, TEX_5);
	else if (nb == 6)
		map_displayer(g, x, y, TEX_6);
	else if (nb == 7)
		map_displayer(g, x, y, TEX_7);
	else if (nb == 8)
		map_displayer(g, x, y, TEX_8);
	else if (nb == 9)
		map_displayer(g, x, y, TEX_9);
}
