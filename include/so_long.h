/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:09:39 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/20 20:27:10 by erpascua         ###   ########.fr       */
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

typedef enum e_tex
{
	TEX_FLOOR,
	TEX_WALL,
	TEX_PLAYER,
	TEX_COLLECT,
	TEX_EXIT,
	NB_TEX
}	t_tex;

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
	void	*tex[NB_TEX];
	int		px;
	int		py;
	int		moves;
}				t_game;

void	print_map(const char *path);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		handle_keypress(int keycode, t_game *game);
void	treatment_map(t_map *map);
int		symbol_counter(t_map *map, char *line, char symbol);
int		check_border(t_map *map, char *line, int row);
int		count_height(t_map *map);
void	load_map(t_game *game, int trigger);
int		window_setup(t_game *game);
void	get_player_init_pos(t_game *game, char *line, int y);
void	map_displayer(t_game *game, int x, int y, t_tex id);

#endif