/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:09:39 by erpascua          #+#    #+#             */
/*   Updated: 2025/07/04 00:46:38 by ubuntu           ###   ########.fr       */
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

# ifndef TILE
#  define TILE 32
# endif
# define TILE_MIN 8
# define ATH_ROWS 1

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
	TEX_PLAYER_LEFT,
	TEX_PLAYER_RIGHT,
	TEX_PLAYER_FRONT,
	TEX_PLAYER_BACK,
	TEX_COLLECT,
	TEX_EXIT,
	TEX_VILAIN,
	ATH_TEX_BG,
	ATH_TEX_PLAYER,
	ATH_TEX_LIFE,
	ATH_TEX_COLLECT,
	ATH_TEX_MOVE,
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

typedef struct s_scale
{
	char	*src;
	char	*dst;
	int		line_size_s;
	int		line_size_d;
	int		bits_per_pxl_s;
	int		bits_per_pxl_d;
	double	ratio_x;
	double	ratio_y;
}				t_scale;

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

typedef struct s_vilain
{
	int	x;
	int	y;
	int	dir;
	int	axis;
	int	frame;
}	t_vilain;

typedef struct s_game
{
	t_map		*map;
	void		*mlx;
	void		*win;
	int			win_w;
	int			win_h;
	int			screen_w;
	int			screen_h;
	int			tile;
	void		*tex[NB_TEX];
	int			cur_lvl;
	int			px;
	int			py;
	char		*ath_path;
	int			ath_cols;
	int			remaining_p_life;
	int			moves;
	t_vilain	s_vilain;
	int			nb_vilains;
}				t_game;

void	print_map(const char *path);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		handle_keypress(int keycode, t_game *g);
void	treatment_map(t_game *g);
int		count_height(t_game *g);
void	load_ath(t_game *g);
void	load_map(t_game *g);
void	load_tex(t_game *g, int id, const char *file);
int		window_setup(t_game *g);
void	get_player_init_pos(t_game *g, char *line, int y);
void	map_displayer(t_game *g, int x, int y, t_tex id);
int		handle_keypress(int keycode, t_game *g);
int		grid_load(t_map *map);
int		close_window(t_game *g);
void	textures_init(t_game *g);
int		is_path_not_solvable(t_game *g);
int		check_border(t_game *g, int fd, char *line, int row);
void	draw_bg(t_game *g, t_tex id);
void	draw_map(t_game *g, char *line, int y);
void	draw_collect(t_game *g, char *line, int y);
void	draw_player(t_game *g, char *line, int y);
void	draw_map_per_pxl(t_game *g, char *row, int *x, int y);
void	draw_ath(t_game *g, char *row);
int		symbol_counter(t_map *map, char *line, char symbol);
void	symbol_increment(t_game *g, char *line);
void	are_symbols_valid(t_map *map);
int		get_ath_cols(const char *path);
void	num_to_xpm(t_game *g, int nb, int x, int y);
void	draw_map_per_pxl(t_game *g, char *row, int *x, int y);
void	destroy_level(t_game *g);
void	destroy_game(t_game *g);
void	grid_free(char **grid);
int		parse_error(t_game *g, int fd, char *line, const char *msg);
int		border_error(char *line, int col);
void	error_exit(t_game *g, char *msg);
void	free_all(t_game *g);
int		update_loop(t_game *g);


#endif
