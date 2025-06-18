/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:56:00 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/18 17:58:31 by erpascua         ###   ########.fr       */
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

int	symbol_counter(t_map *map, char *line, char symbol)
{
	int	n;
	int	col;

	col = 0;
	n = 0;
	while (col < map->width)
	{
		if (line[col] == symbol)
			n++;
		col++;
	}
	return (n);
}

int	check_border(t_map *map, char *line, int row)
{
	int	col;

	col = 0;
	while (col < map->width)
	{
		if (row == 0 || row == map->height - 1)
		{
			if (line[col] != '1')
				return (ft_printf("Error\nChar '%c' is not a '1' (wall)\n",
						line[col]), (0));
		}
		else
		{
			if (col == 0 || col == map->width - 1)
				if (line[col] != '1')
					return (ft_printf("Error\nChar '%c' is not a '1' (wall)\n",
							line[col]), (0));
		}
		col++;
	}
	return (1);
}

int	count_height(t_map *map)
{
	int		fd;
	char	*line;

	fd = open(map->path, O_RDONLY);
	if (fd < 0)
		return (perror("open"), 0);
	map->height = 0;
	while ((line = get_next_line(fd)))
	{
		map->height++;
		free(line);
	}
	close(fd);
	return (map->height);
}

void	are_symbols_valid(t_map *map)
{
	ft_printf("Nb of player | %d |\n", map->count_p);
	ft_printf("Nb of exit | %d |\n", map->count_e);
	ft_printf("Nb of collectibles | %d |\n", map->count_c);
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

int	map_parsing(t_map *map)
{
	int		fd;
	char	*line;
	int		row;
	int		len;

	fd = open(map->path, O_RDONLY);
	map->width = -1;
	row = 0;
	while ((line = get_next_line(fd)))
	{
		len = ft_strlen(line) - (line[ft_strlen(line)-1] == '\n');
		if (map->width == -1)
			map->width = len;
		else if (len != map->width)
			return (free(line), ft_printf("Error\nMap is not rectangular\n"), 0);
		map->count_p += symbol_counter(map, line, 'P');
		map->count_e += symbol_counter(map, line, 'E');
		map->count_c += symbol_counter(map, line, 'C');
		if (!check_border(map, line, row) || !check_cty(map, line))
			return (ft_printf("Error\nMap is not valid.\n"), free(line), 0);
		free(line);
		row++;
	}
	are_symbols_valid(map);
	close(fd);
	return (1);
}

void	treatment_map(t_map *map)
{
	map->height = count_height(map);
	ft_printf("Map parsing value |%d|\n", map_parsing(map));
	if (map_parsing(map))
	{
		printf("Map can be parsed");
	}
}
