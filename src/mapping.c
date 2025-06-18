/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:56:00 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/18 02:07:13 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	is_allowed(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}

int	check_line_conformity(char *line, int width)
{
	int	col;

	col = 0;
	while (col < width)
	{
		if (!is_allowed(line[col]))
			return (ft_printf("Error\nchar '%c' is not valid.\n",
					line[col]), (0));
		col++;
	}
	return (1);
}

int	symbol_counter(char *line, char symbol, int width)
{
	int	n;
	int	col;

	col = 0;
	n = 0;
	while (col < width)
	{
		if (line[col] == symbol)
			n++;
		col++;
	}
	return (n);
}

int	check_line_border(char *line, int row, int height, int width)
{
	int	col;

	col = 0;
	while (col < width)
	{
		if (row == 0 || row == height - 1)
		{
			if (line[col] != '1')
				return (ft_printf("Error\nChar '%c' is not a '1' (wall) for the map's border.\n", line[col]), (0));
		}
		else
		{
			if (col == 0 || col == width - 1)
				if (line[col] != '1')
					return (ft_printf("Error\nchar '%c' is not a '1' (wall) for the map's border.\n", line[col]), (0));
		}
		col++;
	}
	return (1);
}

void	treatment_map(const char *path)
{
	int		fd;
	char	*line;
	int		row;
	int		height;
	int		len;
	int		width;
	int		p;
	int		e;
	int		c;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror("open"), (void)0);
	height = 0;
	while ((line = get_next_line(fd)))
	{
		height++;
		free(line);
	}
	close(fd);
	ft_printf("%d\n", height);
	fd = open(path, O_RDONLY);
	width = -1;
	row = 0;
	p = 0;
	e = 0;
	c = 0;
	while ((line = get_next_line(fd)))
	{
		ft_printf("%s", line);
		len = ft_strlen(line) - (line[ft_strlen(line)-1] == '\n');
		if (width == -1)
			width = len;
		else if (len != width)
			return (free(line), ft_printf("Error\nThe map is not rectangular\n"), (void)0);
		p += symbol_counter(line, 'P', width);
		e += symbol_counter(line, 'E', width);
		c += symbol_counter(line, 'C', width);
		if (!check_line_border(line, row, height, width) || !check_line_conformity(line, width))
			return (ft_printf("Error\nThe map is not valid.\n"), free(line), (void)0);
		free(line);
		row++;
	}
	if (p != 1)
		return (ft_printf("Error\nOne player needed.\n"), (void)0);
	if (e != 1)
		return (ft_printf("Error\nOne exit needed.\n"), (void)0);
	if (c < 1)
		return (ft_printf("Error\nAt least 1 collectible needed.\n"), (void)0);

	close(fd);
	ft_printf("\n");
}
