/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:51:33 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/26 17:43:37 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (!(color & 0xFF))
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(EXIT_SUCCESS);
	return (0);
}

void	level_init(t_game *game)
{
	game->lvl[LEVEL1] = "maps/map1.ber";
	game->lvl[LEVEL2] = "maps/map2.ber";
	game->lvl[LEVEL3] = "maps/map3.ber";
	game->lvl[NB_LVL] = NULL;
	game->cur_lvl = LEVEL0;
}

int	is_map_path_valid(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '.')
			return (ft_strncmp(s + i, ".ber", 5));
		i++;
	}
	return (-1);
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
		if (is_map_path_valid(av[1]))
			return (ft_printf("Error\nThe file is not a .ber\n"), EXIT_FAILURE);
		game.map->path = av[1];
		treatment_map(&game);
		grid_load(&map);
		if (!is_path_solvable(&game))
			return (ft_printf("Error\nMap not solvable\n"), EXIT_FAILURE);
		if (window_setup(&game))
			return (EXIT_FAILURE);
		textures_init(&game);
		load_map(&game);
		load_ath(&game);
		mlx_key_hook(game.win, handle_keypress, &game);
		mlx_hook(game.win, 17, 0, close_window, &game);
		mlx_loop(game.mlx);
	}
	return (0);
}
