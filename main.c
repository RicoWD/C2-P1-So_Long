/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:51:33 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/17 00:53:49 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "include/so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	handle_keypress(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == W || keycode == UP_ARROW)
	{
		__builtin_printf("%s\n", "UP");
	}
	if (keycode == S || keycode == DOWN_ARROW)
	{
		__builtin_printf("%s\n", "DOWN");
	}
	if (keycode == A || keycode == LEFT_ARROW)
	{
		__builtin_printf("%s\n", "LEFT");
	}
	if (keycode == D || keycode == RIGHT_ARROW)
	{
		__builtin_printf("%s\n", "RIGHT");
	}
	// else
	// 	__builtin_printf("%d\n", keycode);
	return (0);
}


int	close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(EXIT_SUCCESS);
	return (0);
}

void texture_fill(t_data *img, int y, int x, int limits_y, int limits_x, int color)
{
	int	cur_x;

	while (y <= limits_y)
	{
		cur_x = x;
		while (cur_x <= limits_x)
		{
			my_mlx_pixel_put(img, y, cur_x, color);
			cur_x++;
		}
		y++;
	}
}

int	main(void)
{
	t_vars	vars;
	t_data	img;
	int	x;
	int y;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "so_long");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img,
			&img.bits_per_pixel, &img.line_length, &img.endian);
	y = 5;
	x = 5;
	texture_fill(&img, y, x, x + 50, y + 50, 0x00FF0000);
	y = 55;
	x = 55;
	texture_fill(&img, y, x, x + 50, y + 50, 0x0000FF00);

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, handle_keypress, &vars);
	mlx_hook(vars.win, 17, 0, close_window, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
