/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:44:37 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/27 16:42:28 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	map_displayer(t_game *game, int x, int y, t_tex id)
{
	mlx_put_image_to_window(game->mlx, game->win, game->tex[id],
		x * TILE, y * TILE);
}

void	draw_bg(t_game *game, t_tex id)
{
	int		y;
	int		x;

	y = 0;
	(void)id;
	while (y < game->map->height * TILE)
	{
		x = 0;
		while (x < game->map->width * TILE)
		{
			map_displayer(game, x, y, id);
			x++;
		}
		y++;
	}
}

void	draw_map(t_game *game, char *line, int y)
{
	int		x;

	x = 0;
	while (x < game->map->width)
	{
		map_displayer(game, x, y, TEX_FLOOR);
		if (line[x] == '1')
			map_displayer(game, x, y, TEX_WALL);
		else if (line[x] == 'E')
			map_displayer(game, x, y, TEX_EXIT);
		else if (line[x] == 'V')
			map_displayer(game, x, y, TEX_VILAIN);
		x++;
	}
}

void	draw_collect(t_game *game, char *line, int y)
{
	int		x;

	x = 0;
	while (x < game->map->width)
	{
		if (line[x] == 'C')
			map_displayer(game, x, y, TEX_COLLECT);
		x++;
	}
}

void	draw_player(t_game *game, char *line, int y)
{
	int		x;

	x = 0;
	while (x < game->map->width)
	{
		if (line[x] == 'P')
			map_displayer(game, x, y, TEX_PLAYER_FRONT);
		x++;
	}
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

void	load_map(t_game *game)
{
	int		fd;
	char	*line;
	int		len;
	int		row;

	fd = open(game->map->path, O_RDONLY);
	if (fd < 0)
		return (perror("open"));
	line = get_next_line(fd);
	if (!line)
		return (perror("open"));
	// textures_init(game);
	// draw_bg(game, TEX_WALL);
	row = 0;
	while (line)
	{
		len = ft_strlen(line) - (line[ft_strlen(line) - 1] == '\n');
		if (game->map->width == -1)
			game->map->width = len;
		draw_map(game, line, row);
		draw_collect(game, line, row);
		draw_player(game, line, row);
		get_player_init_pos(game, line, row);
		line = get_next_line(fd);
		row++;
	}
	close(fd);
}
