/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_conformity_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:34:59 by erpascua          #+#    #+#             */
/*   Updated: 2025/07/01 05:56:15 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	symbol_increment(t_game *g, char *line)
{
	g->map->count_p += symbol_counter(g->map, line, 'P');
	g->map->count_e += symbol_counter(g->map, line, 'E');
	g->map->count_c += symbol_counter(g->map, line, 'C');
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

int	check_border(t_map *map, char *line, int row)
{
	int	col;

	col = 0;
	while (col < map->width)
	{
		if (row == 0 || row == map->height - 1)
		{
			if (line[col] != '1')
			{
				ft_printf("Error\nChar '%c' is not a '1' (wall)\n", line[col]);
				return (0);
			}
		}
		else
		{
			if (col == 0 || col == map->width - 1)
			{
				if (line[col] != '1')
					return (ft_printf("Error\nChar '%c' is not a '1' (wall)\n",
							line[col]), (0));
			}
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
	line = get_next_line(fd);
	while (line)
	{
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
