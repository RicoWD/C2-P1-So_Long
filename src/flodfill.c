/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flodfill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:00:27 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/23 18:27:49 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fills(t_game *game, char target, int row, int col)
{
	if (col < 0 || row < 0 || col > game->map->height || row > game->map->width)
		return ;
	if (game->map->grid[row][col] == 'E' || game->map->grid[row][col] != target)
		return ;
	game->map->grid[row][col] = 'F';
	fills(game, target, row - 1, col);
	fills(game, target, row + 1, col);
	fills(game, target, row, col - 1);
	fills(game, target, row, col + 1);
}

void	flood_fill(t_game *game)
{
	char	target;

	target = game->map->grid[game->py][game->px];

	fills(game, target, game->py, game->px);
}
