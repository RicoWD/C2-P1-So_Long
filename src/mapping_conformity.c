/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_conformity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:56:00 by erpascua          #+#    #+#             */
/*   Updated: 2025/07/02 17:12:26 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_allowed(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E'
		|| c == 'P' || c == 'V');
}

int	check_cty(t_game *g, char *line)
{
	int	col;

	col = 0;
	while (col < g->map->width)
	{
		if (!is_allowed(line[col]))
			return (ft_printf("Error\nchar '%c' is not valid.\n",
					line[col]), close_window(g), 0);
		col++;
	}
	return (1);
}

size_t	strlen_nl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

int	map_parsing(t_game *g, int fd, char *line, int row)
{
	int	len;

	while (line)
	{
		len = strlen_nl(line);
		if (g->map->width == -1)
			g->map->width = len;
		else if (len != g->map->width)
			return (parse_error(g, fd, line, "Map is not rectangular"));
		symbol_increment(g, line);
		if (!check_cty(g, line))
			return (parse_error(g, fd, line, "Unknown char in map"));
		if (!check_border(g, fd, line, row))
			return (parse_error(g, fd, line, "Map is not closed by walls"));
		get_player_init_pos(g, line, row);
		free(line);
		line = get_next_line(fd);
		row++;
	}
	g->map->remaining_c = g->map->count_c;
	are_symbols_valid(g->map);
	close(fd);
	return (1);
}

void	treatment_map(t_game *g)
{
	int		fd;
	char	*line;
	int		row;

	g->map->count_p = 0;
	g->map->count_e = 0;
	g->map->count_c = 0;
	g->map->width = -1;
	g->map->height = 0;
	if (!count_height(g->map))
		return ;
	fd = open(g->map->path, O_RDONLY);
	line = get_next_line(fd);
	row = 0;
	if (!map_parsing(g, fd, line, row))
	{
		destroy_game(g);
		exit(EXIT_FAILURE);
	}
}