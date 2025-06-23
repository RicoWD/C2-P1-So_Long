/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:51:33 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/23 17:50:13 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(EXIT_SUCCESS);
	return (0);
}

// void	texture_fill(t_data *img, int x, int y, int limits_x, int limits_y, int color)
// {
// 	int	cur_y;

// 	while (x <= limits_x)
// 	{
// 		cur_y = y;
// 		while (cur_y <= limits_y)
// 		{
// 			my_mlx_pixel_put(img, x, cur_y, color);
// 			cur_y++;
// 		}
// 		x++;
// 	}
// }

void	level_init(t_game *game)
{
	game->lvl[LEVEL1] = "maps/map1.ber";
	game->lvl[LEVEL2] = "maps/map2.ber";
	game->lvl[LEVEL3] = "maps/map3.ber";
	game->lvl[NB_LVL] = NULL;
	game->cur_lvl = LEVEL0;
}

int	main(int ac, char **av)
{
	t_game	game = {0};
	t_map	map = {0};

	if (ac == 2)
	{
		game.ath_path = "maps/ath.ber";
		game.remaining_p_life = 3;
		game.map = &map;
		level_init(&game);
		game.map->path = av[1];
		treatment_map(&map);
		grid_load(&map);
		if (window_setup(&game))
			return (EXIT_FAILURE);
		load_map(&game);
		load_ath(&game);
		mlx_key_hook(game.win, handle_keypress, &game);
		mlx_hook(game.win, 17, 0, close_window, &game);
		mlx_loop(game.mlx);
	}
	return (0);
}
