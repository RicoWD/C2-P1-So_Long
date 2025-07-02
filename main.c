/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:51:33 by erpascua          #+#    #+#             */
/*   Updated: 2025/07/02 19:35:33 by erpascua         ###   ########.fr       */
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

int	game_launch_checks(t_game *g, char *path)
{
	if (is_map_path_valid(path))
		error_exit(g, "The file is not a '.ber'");
	g->map->path = path;
	treatment_map(g);
	if (grid_load(g->map))
		error_exit(g, "Grid load failed");
	if (!is_path_solvable(g))
		error_exit(g, "Map not solvable");
	g->ath_cols = get_ath_cols(g->ath_path);
	if (window_setup(g))
		error_exit(g, "MLX init failed");
	textures_init(g);
	load_map(g);
	load_ath(g);
	mlx_key_hook(g->win, handle_keypress, g);
	mlx_hook(g->win, 17, 0, close_window, g);
	mlx_loop(g->mlx);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;
	t_map	map;

	ft_memset(&game, 0, sizeof(t_game));
	ft_memset(&map, 0, sizeof(t_map));
	if (ac == 2)
	{
		game.ath_path = "maps/ath.ber";
		game.remaining_p_life = 3;
		game.map = &map;
		game_launch_checks(&game, av[1]);
	}
	return (0);
}
