/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:36:27 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/20 20:39:27 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	if (keycode == W || keycode == UP_ARROW)
	{
		game->py--;
		ft_printf("%s\n", "UP");
		ft_printf("py = %d px = %d\n", game->py, game->px);
		// load_map(game, 0);
		map_displayer(game, game->px, game->py, TEX_PLAYER);

	}
	if (keycode == S || keycode == DOWN_ARROW)
	{
		game->py++;
		ft_printf("%s\n", "DOWN");
		ft_printf("py = %d px = %d\n", game->py, game->px);
		load_map(game, 0);
		map_displayer(game, game->px, game->py, TEX_PLAYER);
	}
	if (keycode == A || keycode == RIGHT_ARROW)
	{
		game->px++;
		ft_printf("%s\n", "LEFT");
		ft_printf("py = %d px = %d\n", game->py, game->px);
		load_map(game, 0);
		map_displayer(game, game->px, game->py, TEX_PLAYER);
	}
	if (keycode == D || keycode == LEFT_ARROW)
	{
		game->px--;
		ft_printf("%s\n", "RIGHT");
		ft_printf("py = %d px = %d\n", game->py, game->px);
		load_map(game, 0);
		map_displayer(game, game->px, game->py, TEX_PLAYER);
	}
	return (0);
}