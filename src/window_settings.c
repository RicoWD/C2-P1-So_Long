/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:28:19 by ep                #+#    #+#             */
/*   Updated: 2025/06/19 03:36:24 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	window_setup(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win = mlx_new_window(game->mlx,
			game->map->width * TILE,
			game->map->height * TILE,
			"Rico's So_Long");
	if (!game->win)
		return (1);
	return (0);
}