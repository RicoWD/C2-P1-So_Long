/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:09:39 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/24 18:59:25 by erpascua         ###   ########.fr       */
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
	TEX_VILAIN,
	ATH_TEX_BG,
	ATH_TEX_HEART,
	ATH_TEX_COLLECT,
	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,
	TEX_4,
	TEX_5,
	TEX_6,
	TEX_7,
	TEX_8,
	TEX_9,
	NB_TEX
}	t_tex;

typedef enum e_lvl
{
	LEVEL0,
	LEVEL1,
	LEVEL2,
	LEVEL3,
	NB_LVL
}	t_lvl;

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
	int		remaining_c;
}				t_map;

typedef struct s_game
{
	t_map	*map;
	void	*mlx;
	void	*win;
	void	*tex[NB_TEX];
	void	*lvl[NB_LVL + 1];
	int		cur_lvl;
	int		px;
	int		py;
	char	*ath_path;
	int		remaining_p_life;
	int		moves;
}				t_game;

void	print_map(const char *path);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		handle_keypress(int keycode, t_game *game);
void	treatment_map(t_game *game);
int		symbol_counter(t_map *map, char *line, char symbol);
int		check_border(t_map *map, char *line, int row);
int		count_height(t_map *map);
void	load_ath(t_game *game);
void	load_map(t_game *game);
void	draw_bg(t_game *game, t_tex id);
int		window_setup(t_game *game);
void	get_player_init_pos(t_game *game, char *line, int y);
void	map_displayer(t_game *game, int x, int y, t_tex id);
int		handle_keypress(int keycode, t_game *game);
void	grid_load(t_map *map);
void	update_ath(t_game *game, int x, int y, int color, char *txt);
int		close_window(t_game *game);
void	textures_init(t_game *game);
int		is_path_solvable(t_game *game);


#endif