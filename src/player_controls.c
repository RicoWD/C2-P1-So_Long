/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:36:27 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/27 16:56:56 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	level_reset(t_game *game)
{
	game->remaining_p_life = 3;
	game->map->remaining_c = game->map->count_c;
	grid_load(game->map);
	load_map(game);
	load_ath(game);
}

void	destroy_level(t_game *game)
{
	int	i;

	i = 0;
	while (i < NB_TEX)
	{
		if (game->tex[i])
		{
			mlx_destroy_image(game->mlx, game->tex[i]);
			game->tex[i] = NULL;
		}
		i++;
	}
}

static void	update_player_pos(t_game *game, int new_x, int new_y, int tex)
{
	game->map->grid[game->py][game->px] = '0';
	map_displayer(game, game->px, game->py, TEX_FLOOR);
	game->px = new_x;
	game->py = new_y;
	game->map->grid[game->py][game->px] = 'P';
	game->moves++;
	load_ath(game);
	ft_printf("Moves: %d\n", game->moves);
	map_displayer(game, game->px, game->py, tex);
}

void	move_player(t_game *game, int new_x, int new_y, int tex)
{
	char	cell;

	if (new_x < 0 || new_x >= game->map->width
		|| new_y < 0 || new_y >= game->map->height)
		return ;
	cell = game->map->grid[new_y][new_x];
	if (cell == '0' || cell == 'C')
	{
		if (cell == 'C')
			game->map->remaining_c--;
		update_player_pos(game, new_x, new_y, tex);
	}
	else if (cell == 'V')
	{
		game->remaining_p_life--;
		load_ath(game);
		ft_printf("Lives remaining %d !\n", game->remaining_p_life);
		if (game->remaining_p_life == 0)
			level_reset(game);
	}
	if (game->map->remaining_c == 0)
		ft_printf("All items collected !\n");
	if (cell == 'E' && game->map->remaining_c > 0)
		ft_printf("Not yet... You still have %d items to collect\n",
			game->map->remaining_c);
	if (cell == 'E' && game->map->remaining_c == 0)
		close_window(game);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	if (keycode == W || keycode == UP_ARROW)
		move_player(game, game->px, game->py - 1, TEX_PLAYER_BACK);
	else if (keycode == S || keycode == DOWN_ARROW)
		move_player(game, game->px, game->py + 1, TEX_PLAYER_FRONT);
	else if (keycode == A || keycode == LEFT_ARROW)
		move_player(game, game->px - 1, game->py, TEX_PLAYER_LEFT);
	else if (keycode == D || keycode == RIGHT_ARROW)
		move_player(game, game->px + 1, game->py, TEX_PLAYER_RIGHT);
	return (0);
}