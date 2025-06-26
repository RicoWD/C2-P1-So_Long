/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:28:19 by ep                #+#    #+#             */
/*   Updated: 2025/06/26 18:00:00 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h> // For exit()

// Forward declaration to avoid implicit declaration warning
static int choose_tile(t_game *g);

#define TILE_MIN  8    /* on refuse plus petit que 8 px */
#ifndef TILE
#define TILE 64        /* valeur par défaut pour TILE si non définie ailleurs */
#endif

static int choose_tile(t_game *g)
{
	int sw;
	int sh;
	int tw;
	int th;

	mlx_get_screen_size(g->mlx, &sw, &sh);
	if (!g->map->width || !g->map->height || g->map->width < 1 || g->map->height < 1)
		return (1);
	if ((g->map->width * TILE_MIN > sw) || (g->map->height * TILE_MIN > sh))
		return (1); /* carte trop grande pour l’écran */

	tw = sw / g->map->width;          /* largeur maxi par tuile  */
	th = sh / g->map->height;         /* hauteur maxi par tuile  */
	if (tw < TILE_MIN || th < TILE_MIN) /* on refuse plus petit que TILE_MIN */
		return (1);                     /* carte trop grande pour l’écran */
	if (tw < th)
		g->tile = tw;
	else
		g->tile = th;
	if (g->tile < TILE_MIN)           /* on ne descend pas en dessous de TILE_MIN */
		g->tile = TILE_MIN;

	if (g->tile > TILE)               /* TILE = valeur demandée au compilo */
		g->tile = TILE;               /* on la prend comme plafond         */

	if (g->tile < TILE_MIN)           /* carte vraiment trop grande        */
		return (1);
	return (0);
}

static void *scale_xpm(void *mlx, const char *file, int tile)
{
	int ws, hs;
	void *src = mlx_xpm_file_to_image(mlx, (char *)file, &ws, &hs);
	if (!src || (ws == tile && hs == tile))
		return (src);

	void *dst = mlx_new_image(mlx, tile, tile);
	int bpp_s, endian_s, bpp_d, endian_d;
	int sl_s, sl_d;
	char *s = mlx_get_data_addr(src, &bpp_s, &sl_s, &endian_s);
	char *d = mlx_get_data_addr(dst, &bpp_d, &sl_d, &endian_d);

	bpp_s /= 8;
	bpp_d /= 8;
	int pitch_s = ws * bpp_s;            /* largeur réelle en octets */
	int pitch_d = tile * bpp_d;

	double rx = (double)ws / tile;
	double ry = (double)hs / tile;

	for (int y = 0; y < tile; y++)
	{
		int sy = (int)(y * ry + 0.5);
		for (int x = 0; x < tile; x++)
		{
			int sx = (int)(x * rx + 0.5);
			*(unsigned int *)(d + y * pitch_d + x * bpp_d) =
			*(unsigned int *)(s + sy * pitch_s + sx * bpp_s);
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
    load_tex(game, TEX_COLLECT, "textures/collect.xpm");
    load_tex(game, TEX_EXIT, "textures/exit.xpm");
    load_tex(game, TEX_VILAIN, "textures/vilain.xpm");
	load_tex(game, ATH_TEX_BG, "textures/ath_bg.xpm");
	load_tex(game, ATH_TEX_HEART, "textures/heart.xpm");
	load_tex(game, ATH_TEX_COLLECT, "textures/ath_collect.xpm");
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

int	window_setup(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		return (1);

	if (choose_tile(g))
	{
		ft_printf("Error\nTile size too small\n");
		if (g->mlx)
		{
			// Free MLX instance if needed (depends on MLX implementation)
			// mlx_destroy_display(g->mlx); // Uncomment if using Linux MLX
			free(g->mlx);
		}
		return (1);
	}

	g->win = mlx_new_window(g->mlx,
			g->map->width  * g->tile,
			g->map->height * g->tile,
			"so_long");
	return (!g->win);
}