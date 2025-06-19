/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ep <ep@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:09:39 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/19 03:19:43 by ep               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>

# ifdef __APPLE__
#  define KEY_ESC 53
# else
#  define KEY_ESC 65307
# endif

# define TILE 64

# define W 119
# define S 115
# define A 100
# define D 97
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

typedef struct s_positions
{
	int	x;
	int	y;
	int	max_x;
	int	max_y;
}				t_positions;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_map
{
	char	**grid;
	char	*path;
	int		width;
	int		height;
	int		count_p;
	int		count_e;
	int		count_c;
}				t_map;

typedef struct s_game
{
	t_map	*map;
	void	*mlx;
	void	*win;
	void	*img_wall;
	void	*img_floor;
	void	*img_player;
	void	*img_collect;
	void	*img_exit;
	int		px;
	int		py;
	int		moves;
	t_data	tiles[5];	
}				t_game;

void	print_map(const char *path);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		handle_keypress(int keycode, t_game *game);
void	treatment_map(t_map *map);
int		symbol_counter(t_map *map, char *line, char symbol);
int		check_border(t_map *map, char *line, int row);
int		count_height(t_map *map);
void	load_map(t_game *game, t_map *map);
int		window_setup(t_game *game);

#endif