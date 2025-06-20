/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_conformity_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:34:59 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/20 19:38:09 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
						line[col]), exit(EXIT_SUCCESS), 0);
		}
		else
		{
			if (col == 0 || col == map->width - 1)
				if (line[col] != '1')
					return (ft_printf("Error\nChar '%c' is not a '1' (wall)\n",
							line[col]), (0), exit(EXIT_SUCCESS), 0);
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
