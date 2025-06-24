/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_conformity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:56:00 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/24 19:19:56 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_allowed(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' ||
		c == 'P' || c == 'V');
}

int	check_cty(t_map *map, char *line)
{
	int	col;

	col = 0;
	while (col < map->width)
	{
		if (!is_allowed(line[col]))
			return (ft_printf("Error\nchar '%c' is not valid.\n",
					line[col]), (0));
		col++;
	}
	return (1);
}

void	are_symbols_valid(t_map *map)
{
	if (map->count_p != 1)
		return (ft_printf("Error\nOne player needed.\n"),
			exit(EXIT_SUCCESS), (void)0);
	if (map->count_e != 1)
		return (ft_printf("Error\nOne exit needed.\n"),
			exit(EXIT_SUCCESS), (void)0);
	if (map->count_c < 1)
		return (ft_printf("Error\nAt least 1 collectible needed.\n"),
			exit(EXIT_SUCCESS), (void)0);
}

int	map_parsing(t_game *game, int fd, char *line, int row)
{
	int		len;

	while (line)
	{
		len = ft_strlen(line) - (line[ft_strlen(line) - 1] == '\n');
		if (game->map->width == -1)
			game->map->width = len;
		else if (len != game->map->width)
			return (free(line), ft_printf("Error\nMap is not rectangular\n"),
				exit(EXIT_SUCCESS), 0);
		game->map->count_p += symbol_counter(game->map, line, 'P');
		game->map->count_e += symbol_counter(game->map, line, 'E');
		game->map->count_c += symbol_counter(game->map, line, 'C');
		if (!check_cty(game->map, line))
			return (free(line), exit(EXIT_SUCCESS), 0);
		if (!check_border(game->map, line, row))
			return (ft_printf("Error\nMap is not valid.\n"), free(line), 0);
		get_player_init_pos(game, line, row);
		free(line);
		line = get_next_line(fd);
		row++;
	}
	game->map->remaining_c = game->map->count_c;
	are_symbols_valid(game->map);
	close(fd);
	return (1);
}

void	treatment_map(t_game *game)
{
	int		fd;
	char	*line;
	int		row;

	game->map->count_p = 0;
	game->map->count_e = 0;
	game->map->count_c = 0;
	game->map->width = -1;
	game->map->height = 0;
	if (!count_height(game->map))
		return ;
	fd = open(game->map->path, O_RDONLY);
	line = get_next_line(fd);
	row = 0;
	map_parsing(game, fd, line, row);
}
