/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:09:39 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/17 17:48:59 by erpascua         ###   ########.fr       */
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
#  include <X11/keysym.h>
#  define KEY_ESC XK_Escape
# endif

# define W 119
# define S 115
# define A 100
# define D 97
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_game
{
	char	**map;
	int		width;
	int		height;
	int		px;
	int		py;
	int		n_collect;
	int		moves;
	void	*mlx;
	void	*win;
	t_data	tiles[5];	
}				t_game;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		count_p;
	int		count_e;
	int		count_c;
}				t_map;

void	print_map(const char *path);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		handle_keypress(int keycode, t_game *vars);
void	treatment_map(const char *path);

#endif