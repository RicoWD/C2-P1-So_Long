/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ath_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:18:20 by ubuntu            #+#    #+#             */
/*   Updated: 2025/06/23 01:57:02 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

// void	update_ath(t_game *game, int x, int y, int color, char *txt)
// {
// 	mlx_string_put(game->mlx, game->win, x, y, color, txt);
// }

void	num_to_xpm(t_game *game, int nb, int x, int y)
{
	if (nb == 0)
		map_displayer(game, x, y, TEX_0);
	else if (nb == 1)
		map_displayer(game, x, y, TEX_1);
	else if (nb == 2)
		map_displayer(game, x, y, TEX_2);
	else if (nb == 3)
		map_displayer(game, x, y, TEX_3);
	else if (nb == 4)
		map_displayer(game, x, y, TEX_4);
	else if (nb == 5)
		map_displayer(game, x, y, TEX_5);
	else if (nb == 6)
		map_displayer(game, x, y, TEX_6);
	else if (nb == 7)
		map_displayer(game, x, y, TEX_7);
	else if (nb == 8)
		map_displayer(game, x, y, TEX_8);
	else if (nb == 9)
		map_displayer(game, x, y, TEX_9);
}

static void draw_number(t_game *game, int value, int x, int y)
{
    char	*s;
    size_t	i;
	
	s = ft_itoa(value);
	i  = 0;
    while (i < ft_strlen(s) && x + (int)i < game->map->width)
    {
        num_to_xpm(game, s[i] - '0', x + i, y);
        i++;
    }
    free(s);
}

static void draw_ath(t_game *game, char *row)
{
    int y;
    int x;

	y = game->map->height;
	x = 0;
    while (x < game->map->width)
        map_displayer(game, x++, y, ATH_TEX_BG);
    x = 0;
    while (row[x] && x < game->map->width)
    {
        if (row[x] == 'S')
            map_displayer(game, x, y, ATH_TEX_BG);
        else if (row[x] == 'H')
            map_displayer(game, x, y, ATH_TEX_HEART);
        else if (row[x] == 'P')
            map_displayer(game, x, y, TEX_PLAYER);
		else if (row[x] == 'c')
		{
    		draw_number(game, game->map->remaining_c, x, y);
			// x += (int)ft_strlen(row) - 1;
		}
	    else if (row[x] == 'C')
            map_displayer(game, x, y, TEX_COLLECT);
		else if (row[x] == 'm' )
		{
		 	draw_number(game, game->moves, x, y);
			// x += (int)ft_strlen(row) - 1;
		}
		else if (row[x] == 'M')
			map_displayer(game, x, y, TEX_COLLECT);
        x++;
    }
}


void load_ath(t_game *g)
{
    int  fd  = open(g->ath_path, O_RDONLY);
    char *line;

    if (fd < 0 || !(line = get_next_line(fd)))
        return ((void)perror("ATH"));

    draw_ath(g, line);
    free(line);
    close(fd);
}