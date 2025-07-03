/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:41:48 by erpascua          #+#    #+#             */
/*   Updated: 2025/07/03 20:41:53 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	border_error(char *line, int col)
{
	ft_printf("Error\nChar '%c' is not a '1' (wall)\n", line[col]);
	if (line)
		free(line);
	return (0);
}

void	error_exit(t_game *g, char *msg)
{
	if (msg)
		ft_printf("Error\n%s\n", msg);
	destroy_game(g);
	exit(EXIT_FAILURE);
}

int	parse_error(t_game *g, int fd, char *line, const char *msg)
{
	close(fd);
	get_next_line(fd);
	if (msg)
		ft_printf("Error\n%s\n", msg);
	if (line)
		free(line);
	if (g->map && g->map->grid)
		grid_free(g->map->grid);
	exit(EXIT_FAILURE);
}
