/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:13:13 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/19 03:38:15 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_pxl(t_game *game, char symbol, int col, int row)
{
	void	*img;

	img = NULL;
	if (symbol == '0')
		img = game->img_floor;
	else if (symbol == '1')
		img = game->img_wall;
	else if (symbol == 'P')
		img = game->img_player;
	else if (symbol == 'C')
		img = game->img_collect;
	else if (symbol == 'E')
		img = game->img_exit;
	if (img)
		mlx_put_image_to_window(game->mlx, game->win, img,
			col * TILE, row * TILE);
}

void	symbol_assignement(t_game *game, t_map *map, char *line, int row)
{
	int	col;

	col = 0;
	while (col < map->width && line[col] && line[col] != '\n')
	{
		display_pxl(game, line[col], col, row);
		col++;
	}
	ft_printf("\n");
}

void	map_reading(t_game *game, t_map *map, int fd, char *line)
{
	int	len;
	int	row;

	row = 0;
	while (line)
	{
		len = ft_strlen(line) - (line[ft_strlen(line) - 1] == '\n');
		if (map->width == -1)
			map->width = len;
		symbol_assignement(game, map, line, row);
		row++;
		line = get_next_line(fd);
	}
	map->height = row;
}

void	textures_init(t_game *game)
{
	int	w;
	int	h;

	w = TILE;
	h = TILE;
	game->img_wall = mlx_xpm_file_to_image(game->mlx,
			"textures/wall.xpm", &w, &h);
	game->img_floor = mlx_xpm_file_to_image(game->mlx,
			"textures/floor.xpm", &w, &h);
	game->img_player = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &w, &h);
	game->img_collect = mlx_xpm_file_to_image(game->mlx,
			"textures/collect.xpm", &w, &h);
	game->img_exit = mlx_xpm_file_to_image(game->mlx,
			"textures/exit.xpm", &w, &h);
}

// void	textures_init(t_game *game, t_map *map)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = 0;
// 	while (y < map->height)
// 	{
// 		while (x < map->width)
// 		{
// 			textures_assignements(game, x, y);
// 			x++;
// 		}
// 		y++;
// 	}
// }

void	load_map(t_game *game, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(map->path, O_RDONLY);
	if (fd < 0)
		return (perror("open"));
	line = get_next_line(fd);
	if (!line)
		return (perror("open"));
	textures_init(game);
	map_reading(game, map, fd, line);
	close(fd);
}
