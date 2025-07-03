/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:43:47 by ubuntu            #+#    #+#             */
/*   Updated: 2025/07/03 13:46:09 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// void	grid_free(char **grid, int height)
// {
// 	int	i;

// 	if (!grid)
// 		return ;
// 	i = 0;
// 	while (i < height && grid[i])
// 	{
// 		free(grid[i]);
// 		i++;
// 	}
// 	free(grid);
// }

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

void	destroy_level(t_game *g)
{
	int	i;

	i = 0;
	while (i < NB_TEX)
	{
		if (g->tex[i])
		{
			mlx_destroy_image(g->mlx, g->tex[i]);
			g->tex[i] = NULL;
		}
		i++;
	}
}

void	destroy_game(t_game *g)
{
	int	i;

	i = 0;
	if (!g || !g->mlx)
		return ;
	while (i < NB_TEX)
	{
		if (g->tex[i])
		{
			mlx_destroy_image(g->mlx, g->tex[i]);
			g->tex[i] = NULL;
		}
		i++;
	}
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	if (g->map && g->map->grid)
		grid_free(g->map->grid);
	mlx_destroy_display(g->mlx);
	free(g->mlx);
}

int	close_window(t_game *g)
{
	destroy_game(g);
	exit(EXIT_SUCCESS);
}
