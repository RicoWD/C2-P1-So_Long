/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:51:33 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/18 18:26:11 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	if (keycode == W || keycode == UP_ARROW)
	{
		ft_printf("%s\n", "UP");
	}
	if (keycode == S || keycode == DOWN_ARROW)
	{
		ft_printf("%s\n", "DOWN");
	}
	if (keycode == A || keycode == LEFT_ARROW)
	{
		ft_printf("%s\n", "LEFT");
	}
	if (keycode == D || keycode == RIGHT_ARROW)
	{
		ft_printf("%s\n", "RIGHT");
	}
	// else
	// 	ft_printf("%d\n", keycode);
	return (0);
}



int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(EXIT_SUCCESS);
	return (0);
}

void texture_fill(t_data *img, int x, int y, int limits_x, int limits_y, int color)
{
	int	cur_y;

	while (x <= limits_x)
	{
		cur_y = y;
		while (cur_y <= limits_y)
		{
			my_mlx_pixel_put(img, x, cur_y, color);
			cur_y++;
		}
		x++;
	}
}

int	main(void)
{
	t_game	game = {0};
	t_map	map = {0};
	t_data	img;
	int		x;
	int		y;
	int		max_x;
	int		max_y;

	map.path = "maps/map1.ber";
	game.map = &map;
	treatment_map(&map);

	max_x = 800;
	max_y = 500;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, max_x, max_y, "so_long");
	img.img = mlx_new_image(game.mlx, max_x, max_y);
	img.addr = mlx_get_data_addr(img.img,
			&img.bits_per_pixel, &img.line_length, &img.endian);
	y = 0;
	x = 0;
	texture_fill(&img, x, y, max_x, y + 50, 0x00FF0000);
	texture_fill(&img, x, y, x + 50, max_y, 0x00FF0000);
	texture_fill(&img, max_x - 50, y, max_x, max_y, 0x00FF0000);
	texture_fill(&img, x, max_y - 50, max_x, max_y, 0x00FF0000);
	y = 55;
	x = 55;
	texture_fill(&img, y, x, x + 50, y + 50, 0x0000FF00);

	mlx_put_image_to_window(game.mlx, game.win, img.img, 0, 0);
	mlx_key_hook(game.win, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
