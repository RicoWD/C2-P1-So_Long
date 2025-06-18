/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:13:13 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/18 19:44:49 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_pxl(char symbol)
{
	if (symbol == '0')
	{
		ft_printf(" ");
	}
	if (symbol == '1')
	{
		ft_printf("+");
	}
	if (symbol == 'P')
	{
		ft_printf("*");
	}
	if (symbol == 'C')
	{
		ft_printf("$");
	}
	if (symbol == 'E')
	{
		ft_printf("|");
	}
}

void	symbol_assignement(t_map *map, char *line)
{
	int	col;

	col = 0;
	while (col < map->width)
	{
		if (line[col] == '1')
		{
			display_pxl(line[col]);
		}
		col++;
	}
}

void	map_reading(t_map *map, int fd, char *line, int row)
{
	int	len;

	while (line)
	{
		len = ft_strlen(line) - (line[ft_strlen(line) - 1] == '\n');
		if (map->width == -1)
			map->width = len;
		symbol_assignement(map, line);
	}
}

void	load_map(t_map *map)
{
	int		fd;
	char	*line;
	int		row;

	fd = open(map->path, O_RDONLY);
	line = get_next_line(fd);
	row = 0;
	map_reading(map, fd, line, row)
}