/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:51:33 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/17 17:50:16 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	handle_keypress(int keycode, t_game *vars)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
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



int	close_window(t_game *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
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
	t_game	vars;
	t_data	img;
	int		x;
	int		y;
	int		max_x;
	int		max_y;

	treatment_map("maps/map1.ber");

	max_x = 800;
	max_y = 500;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, max_x, max_y, "so_long");
	img.img = mlx_new_image(vars.mlx, max_x, max_y);
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

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, handle_keypress, &vars);
	mlx_hook(vars.win, 17, 0, close_window, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
