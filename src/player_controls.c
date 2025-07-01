/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:36:27 by erpascua          #+#    #+#             */
/*   Updated: 2025/07/01 06:00:18 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	level_reset(t_game *g)
{
	g->remaining_p_life = 3;
	g->map->remaining_c = g->map->count_c;
	grid_load(g->map);
	load_map(g);
	load_ath(g);
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

static void	update_player_pos(t_game *g, int new_x, int new_y, int tex)
{
	g->map->grid[g->py][g->px] = '0';
	map_displayer(g, g->px, g->py, TEX_FLOOR);
	g->px = new_x;
	g->py = new_y;
	g->map->grid[g->py][g->px] = 'P';
	g->moves++;
	load_ath(g);
	ft_printf("Moves: %d\n", g->moves);
	map_displayer(g, g->px, g->py, tex);
}

void	move_player(t_game *g, int new_x, int new_y, int tex)
{
	char	cell;

	if (new_x < 0 || new_x >= g->map->width
		|| new_y < 0 || new_y >= g->map->height)
		return ;
	cell = g->map->grid[new_y][new_x];
	if (cell == '0' || cell == 'C')
	{
		if (cell == 'C')
			g->map->remaining_c--;
		update_player_pos(g, new_x, new_y, tex);
	}
	else if (cell == 'V')
	{
		g->remaining_p_life--;
		load_ath(g);
		ft_printf("Lives remaining %d !\n", g->remaining_p_life);
		if (g->remaining_p_life == 0)
			level_reset(g);
	}
	if (cell == 'E' && g->map->remaining_c > 0)
		ft_printf("Not yet... You still have %d items to collect\n",
			g->map->remaining_c);
	if (cell == 'E' && g->map->remaining_c == 0)
		close_window(g);
}

int	handle_keypress(int keycode, t_game *g)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(g->mlx, g->win);
		exit(0);
	}
	if (keycode == W || keycode == UP_ARROW)
		move_player(g, g->px, g->py - 1, TEX_PLAYER_BACK);
	else if (keycode == S || keycode == DOWN_ARROW)
		move_player(g, g->px, g->py + 1, TEX_PLAYER_FRONT);
	else if (keycode == A || keycode == LEFT_ARROW)
		move_player(g, g->px - 1, g->py, TEX_PLAYER_LEFT);
	else if (keycode == D || keycode == RIGHT_ARROW)
		move_player(g, g->px + 1, g->py, TEX_PLAYER_RIGHT);
	return (0);
}
