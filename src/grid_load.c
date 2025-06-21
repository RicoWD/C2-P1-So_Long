/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:34:59 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/20 19:38:09 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*line_ndup(char *line, size_t size)
{
	char	*l;
	size_t	i;

	l = malloc (size);
	if (!l)
		return (NULL);
	while (i < size)
	{
		l[i] = line[i];
		i++;
	}
	return (l);
}

void    grid_load(t_map *map)
{
    int     fd;
    char    *line;
    int     row;

	fd = open(map->path, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	map->grid = malloc (map->height * sizeof(char *));
	if (!map->grid)
		exit(EXIT_FAILURE);
	line = get_next_line(fd);
	while (line)
	{

		map->grid[row] = line_ndup(line, map->width);
		row++;
		line = get_next_line(fd);
	}
	close(fd);
}