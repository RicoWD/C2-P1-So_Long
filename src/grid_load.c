/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:34:59 by erpascua          #+#    #+#             */
/*   Updated: 2025/07/03 20:50:45 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*line_ndup(char *line, int width)
{
	char	*dst;
	int		i;

	dst = malloc(width + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < width && line[i] && line[i] != '\n')
	{
		dst[i] = line[i];
		i++;
	}
	while (i < width)
		dst[i++] = '1';
	dst[i] = '\0';
	return (dst);
}

char	**grid_alloc(int h)
{
	char	**g;

	g = malloc(sizeof(char *) * (h + 1));
	if (!g)
		return (NULL);
	g[h] = NULL;
	return (g);
}

int	grid_load(t_map *m)
{
	int		fd;
	char	*line;
	int		row;

	if (m->grid)
		grid_free(m->grid);
	fd = open(m->path, O_RDONLY);
	if (fd < 0)
		return (close(fd), 1);
	m->grid = grid_alloc(m->height);
	if (!m->grid)
		return (close(fd), 1);
	row = 0;
	line = get_next_line(fd);
	while (line)
	{
		m->grid[row] = line_ndup(line, m->width);
		free(line);
		if (!m->grid[row++])
			return (close(fd), 1);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
