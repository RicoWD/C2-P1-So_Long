/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:44:37 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/24 19:23:33 by erpascua         ###   ########.fr       */
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
			map_displayer(game, x, y, TEX_PLAYER);
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

void	textures_init(t_game *game)
{
	game->tex[TEX_WALL] = load_xpm(game->mlx, "textures/wall.xpm");
	game->tex[TEX_FLOOR] = load_xpm(game->mlx, "textures/floor.xpm");
	game->tex[TEX_PLAYER] = load_xpm(game->mlx, "textures/player.xpm");
	game->tex[TEX_COLLECT] = load_xpm(game->mlx, "textures/collect.xpm");
	game->tex[TEX_VILAIN] = load_xpm(game->mlx, "textures/vilain.xpm");
	game->tex[TEX_EXIT] = load_xpm(game->mlx, "textures/exit.xpm");
	game->tex[ATH_TEX_BG] = load_xpm(game->mlx, "textures/ath_bg.xpm");
	game->tex[ATH_TEX_HEART] = load_xpm(game->mlx, "textures/heart.xpm");
	game->tex[ATH_TEX_COLLECT] = load_xpm(game->mlx,
			"textures/ath_collect.xpm");
	game->tex[TEX_0] = load_xpm(game->mlx, "textures/alphanum/0.xpm");
	game->tex[TEX_1] = load_xpm(game->mlx, "textures/alphanum/1.xpm");
	game->tex[TEX_2] = load_xpm(game->mlx, "textures/alphanum/2.xpm");
	game->tex[TEX_3] = load_xpm(game->mlx, "textures/alphanum/3.xpm");
	game->tex[TEX_4] = load_xpm(game->mlx, "textures/alphanum/4.xpm");
	game->tex[TEX_5] = load_xpm(game->mlx, "textures/alphanum/5.xpm");
	game->tex[TEX_6] = load_xpm(game->mlx, "textures/alphanum/6.xpm");
	game->tex[TEX_7] = load_xpm(game->mlx, "textures/alphanum/7.xpm");
	game->tex[TEX_8] = load_xpm(game->mlx, "textures/alphanum/8.xpm");
	game->tex[TEX_9] = load_xpm(game->mlx, "textures/alphanum/9.xpm");
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
	textures_init(game);
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
