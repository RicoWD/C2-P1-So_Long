/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:36:27 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/23 17:29:34 by erpascua         ###   ########.fr       */
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
			mlx_destroy_image(game->mlx, game->tex[i]);
		game->tex[i] = NULL;
		i++;
	}
}

int	next_level(t_game *game)
{
	game->cur_lvl++;
	printf("LEVEL %d", game->cur_lvl);
	if (game->lvl[game->cur_lvl] == NULL)
	{
		ft_printf("✅ All level completed... Nice work! ✅\n");
		close_window(game);
		return (0);
	}
	destroy_level(game);
	game->map->path = game->lvl[game->cur_lvl];
	treatment_map(game->map);
	mlx_destroy_window(game->mlx, game->win);
	game->win = mlx_new_window(game->mlx,
			game->map->width * TILE,
			(game->map->height + 1) * TILE, "so_long");
	game->remaining_p_life = 3;
	game->map->remaining_c = game->map->count_c;
	game->moves = 0;
	textures_init(game);
	load_map(game);
	load_ath(game);
	mlx_key_hook(game->win, handle_keypress, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	return (0);
}

void	move_player(t_game *game, int new_x, int new_y)
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
		load_ath(game);
		ft_printf("Moves: %d\n", game->moves);
		map_displayer(game, game->px, game->py, TEX_PLAYER);
	}
	if (game->map->grid[new_y][new_x] == 'V')
	{
		game->remaining_p_life--;
		load_ath(game);
		ft_printf("Lives remaining %d !\n", game->remaining_p_life);
		if (game->remaining_p_life == 0)
			level_reset(game);
	}
	if (game->map->remaining_c == 0)
		ft_printf("All items collected !\n");
	if (game->map->grid[new_y][new_x] == 'E' && game->map->remaining_c > 0)
		ft_printf("Not yet... You still have %d items to collect\n", game->map->remaining_c);
	if (game->map->grid[new_y][new_x] == 'E' && game->map->remaining_c == 0)
		next_level(game);
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
	}
	if (keycode == S || keycode == DOWN_ARROW)
	{
		ft_printf("%s\n", "DOWN");
		move_player(game, game->px, game->py + 1);
	}
	if (keycode == A || keycode == RIGHT_ARROW)
	{
		ft_printf("%s\n", "LEFT");
		move_player(game, game->px + 1, game->py);
	}
	if (keycode == D || keycode == LEFT_ARROW)
	{
		ft_printf("%s\n", "RIGHT");
		move_player(game, game->px - 1, game->py);
	}
	return (0);
}