/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:44:37 by erpascua          #+#    #+#             */
/*   Updated: 2025/07/03 15:49:20 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	map_displayer(t_game *g, int x, int y, t_tex id)
{
	mlx_put_image_to_window(g->mlx, g->win, g->tex[id],
		x * TILE, y * TILE);
}

void	*load_xpm(void *mlx, const char *path)
{
	int		w;
	int		h;
	void	*img;

	img = mlx_xpm_file_to_image(mlx, (char *)path, &w, &h);
	if (!img)
	{
		ft_printf("Error\nmlx_xpm_file_to_image: %s\n", path);
		exit(EXIT_FAILURE);
	}
	return (img);
}

void	load_map(t_game *g)
{
	int		fd;
	char	*line;
	int		len;
	int		row;

	fd = open(g->map->path, O_RDONLY);
	if (fd < 0)
		return ((void)close(fd), (void)get_next_line(fd));
	line = get_next_line(fd);
	if (!line)
		return ((void)close(fd), (void)get_next_line(fd), free(line),
			error_exit(g, "Line not found"));
	row = 0;
	while (line)
	{
		len = ft_strlen(line) - (line[ft_strlen(line) - 1] == '\n');
		if (g->map->width == -1)
			g->map->width = len;
		draw_map(g, line, row);
		draw_collect(g, line, row);
		draw_player(g, line, row);
		get_player_init_pos(g, line, row);
		free(line);
		line = get_next_line(fd);
		row++;
	}
	close(fd);
}
