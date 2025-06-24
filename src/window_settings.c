/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:28:19 by ep                #+#    #+#             */
/*   Updated: 2025/06/24 16:23:26 by erpascua         ###   ########.fr       */
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
			(game->map->height + 1) * TILE,
			"Rico's So_Long");
	if (!game->win)
		return (1);
	return (0);
}
