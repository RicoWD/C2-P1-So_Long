/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:36:27 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/21 01:38:52 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void move_player(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map->width || new_y < 0 || new_y >= game->map->height)
		return;
	if (game->map->grid[new_y][new_x] == '0' || game->map->grid[new_y][new_x] == 'C')
	{
		if (game->map->grid[new_y][new_x] == 'C')
			game->map->remaining_c--;
		game->map->grid[game->py][game->px] = '0';
		map_displayer(game, game->px, game->py, TEX_FLOOR);
		game->px = new_x;
		game->py = new_y;
		game->map->grid[game->py][game->px] = 'P';
		game->moves++;
		ft_printf("Moves: %d\n", game->moves);
		map_displayer(game, game->px, game->py, TEX_PLAYER);
	}
	if (game->map->remaining_c == 0)
		ft_printf("All items collected !\n");
	if (game->map->grid[new_y][new_x] == 'E' && game->map->remaining_c > 0)
		ft_printf("Not yet... You still have %d items to collect\n", game->map->remaining_c);
	if (game->map->grid[new_y][new_x] == 'E' && game->map->remaining_c == 0)
		exit(EXIT_SUCCESS);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	if (keycode == W || keycode == UP_ARROW)
	{
		ft_printf("%s\n", "UP");
		move_player(game, game->px, game->py - 1);
		// map_displayer(game, game->px, game->py, TEX_PLAYER);
	}
	if (keycode == S || keycode == DOWN_ARROW)
	{
		ft_printf("%s\n", "DOWN");
		move_player(game, game->px, game->py + 1);
		//load_map(game, 0);
		//map_displayer(game, game->px, game->py, TEX_PLAYER);
	}
	if (keycode == A || keycode == RIGHT_ARROW)
	{
		ft_printf("%s\n", "LEFT");
		move_player(game, game->px + 1, game->py);
		//ft_printf("py = %d px = %d\n", game->py, game->px);
		//load_map(game, 0);
		//map_displayer(game, game->px, game->py, TEX_PLAYER);
	}
	if (keycode == D || keycode == LEFT_ARROW)
	{
		ft_printf("%s\n", "RIGHT");
		move_player(game, game->px - 1, game->py);
		//ft_printf("py = %d px = %d\n", game->py, game->px);
		//load_map(game, 0);
		//map_displayer(game, game->px, game->py, TEX_PLAYER);
	}
	return (0);
}