/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_conformity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:56:00 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/18 19:15:51 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_allowed(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
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

int	map_parsing(t_map *map, int fd, char *line, int row)
{
	int		len;

	while (line)
	{
		len = ft_strlen(line) - (line[ft_strlen(line) - 1] == '\n');
		if (map->width == -1)
			map->width = len;
		else if (len != map->width)
			return (free(line), ft_printf("Error\nMap is not rectangular\n"),
				exit(EXIT_SUCCESS), 0);
		map->count_p += symbol_counter(map, line, 'P');
		map->count_e += symbol_counter(map, line, 'E');
		map->count_c += symbol_counter(map, line, 'C');
		if (!check_border(map, line, row) || !check_cty(map, line))
			return (ft_printf("Error\nMap is not valid.\n"), free(line), 0);
		free(line);
		line = get_next_line(fd);
		row++;
	}
	are_symbols_valid(map);
	close(fd);
	return (1);
}

void	treatment_map(t_map *map)
{
	int		fd;
	char	*line;
	int		row;

	map->count_p = 0;
	map->count_e = 0;
	map->count_c = 0;
	map->width = -1;
	map->height = 0;
	map->height = count_height(map);
	fd = open(map->path, O_RDONLY);
	line = get_next_line(fd);
	row = 0;
	if (map_parsing(map, fd, line, row))
		printf("Map can be parsed");
}
