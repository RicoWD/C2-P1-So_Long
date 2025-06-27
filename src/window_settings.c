/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:28:19 by ep                #+#    #+#             */
/*   Updated: 2025/06/27 17:07:44 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define TILE_MIN  8
#define ATH_ROWS  1          /* nombre de lignes pour l’ATH */

static int choose_tile(t_game *g)
{
    int sw, sh;                          /* taille écran            */
    int tw, th;                          /* tuile max largeur/haut. */

    mlx_get_screen_size(g->mlx, &sw, &sh);

    /* espace vertical réservé au HUD */
    int free_h = sh - ATH_ROWS * TILE_MIN;   /* valeur min => sûr d'afficher HUD */

    tw =  sw / g->map->width;
    th = free_h / g->map->height;

    g->tile = (tw < th) ? tw : th;        /* plus petite des deux    */
    if (g->tile > TILE)                  /* TILE demandé au compilo */
        g->tile = TILE;
    if (g->tile < TILE_MIN)
        return (1);                      /* vraiment trop grand     */
    return (0);
}


void *scale_xpm(void *mlx, const char *file, int tile)
{
    int ws, hs;
    void *src = mlx_xpm_file_to_image(mlx, (char *)file, &ws, &hs);
    if (!src || (ws == tile && hs == tile))
        return (src);

    void *dst = mlx_new_image(mlx, tile, tile);

    int bpp_s, sl_s, endian_s;
    int bpp_d, sl_d, endian_d;
    char *s = mlx_get_data_addr(src, &bpp_s, &sl_s, &endian_s);
    char *d = mlx_get_data_addr(dst, &bpp_d, &sl_d, &endian_d);

    bpp_s /= 8;  bpp_d /= 8;

    double rx = (double)ws / tile;
    double ry = (double)hs / tile;

    for (int y = 0; y < tile; y++)
    {
        int sy = (int)(y * ry + 0.5);
        for (int x = 0; x < tile; x++)
        {
            int sx = (int)(x * rx + 0.5);
            *(unsigned int *)(d + y * sl_d + x * bpp_d) =
            *(unsigned int *)(s + sy * sl_s + sx * bpp_s);
        }
    }
    mlx_destroy_image(mlx, src);
    return (dst);
}



static void	load_tex(t_game *game, int id, const char *file)
{
	game->tex[id] = scale_xpm(game->mlx, file, game->tile);
	if (!game->tex[id])
	{
		ft_printf("Error\ntexture: %s\n", file);
		exit(EXIT_FAILURE);
	}
}

void	textures_init(t_game *game)
{
    load_tex(game, TEX_WALL, "textures/wall.xpm");
    load_tex(game, TEX_FLOOR, "textures/floor.xpm");
    load_tex(game, TEX_PLAYER, "textures/player.xpm");
	load_tex(game, TEX_PLAYER_LEFT, "textures/player_left.xpm");
	load_tex(game, TEX_PLAYER_RIGHT, "textures/player_right.xpm");
	load_tex(game, TEX_PLAYER_FRONT, "textures/player_front.xpm");
	load_tex(game, TEX_PLAYER_BACK, "textures/player_back.xpm");
    load_tex(game, TEX_COLLECT, "textures/collect.xpm");
    load_tex(game, TEX_EXIT, "textures/exit.xpm");
    load_tex(game, TEX_VILAIN, "textures/vilain.xpm");
	load_tex(game, ATH_TEX_BG, "textures/ath_bg.xpm");
	load_tex(game, ATH_TEX_LIFE, "textures/ath_life.xpm");
	load_tex(game, ATH_TEX_COLLECT, "textures/ath_collect.xpm");
	load_tex(game, ATH_TEX_MOVE, "textures/ath_moves.xpm");
	load_tex(game, ATH_TEX_PLAYER, "textures/ath_player.xpm");
	load_tex(game, TEX_0, "textures/alphanum/0.xpm");
	load_tex(game, TEX_1, "textures/alphanum/1.xpm");
	load_tex(game, TEX_2, "textures/alphanum/2.xpm");
	load_tex(game, TEX_3, "textures/alphanum/3.xpm");
	load_tex(game, TEX_4, "textures/alphanum/4.xpm");
	load_tex(game, TEX_5, "textures/alphanum/5.xpm");
	load_tex(game, TEX_6, "textures/alphanum/6.xpm");
	load_tex(game, TEX_7, "textures/alphanum/7.xpm");
	load_tex(game, TEX_8, "textures/alphanum/8.xpm");
	load_tex(game, TEX_9, "textures/alphanum/9.xpm");
}

int window_setup(t_game *g)
{
    g->mlx = mlx_init();
    if (!g->mlx)
        return (1);

    if (choose_tile(g))
        return (ft_printf("Error\nMap too big for screen\n"), 1);

    g->win = mlx_new_window(g->mlx,
            g->map->width  * g->tile,
            (g->map->height + ATH_ROWS) * g->tile,
            "so_long");
    return (!g->win);
}
