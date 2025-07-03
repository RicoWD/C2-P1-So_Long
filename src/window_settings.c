/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:28:19 by ep                #+#    #+#             */
/*   Updated: 2025/07/03 20:42:40 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	choose_tile(t_game *g)
{
	int	ref_w;
	int	ref_h;
	int	tile_w;

	mlx_get_screen_size(g->mlx, &g->screen_w, &g->screen_h);
	ref_w = g->map->width;
	if (g->ath_cols + 2 > ref_w)
		ref_w = g->ath_cols + 2;
	ref_h = g->map->height + ATH_ROWS;
	tile_w = g->screen_w / ref_w;
	g->tile = g->screen_h / ref_h;
	if (tile_w < g->tile)
		g->tile = tile_w;
	if (g->tile > TILE)
		g->tile = TILE;
	if (g->tile < TILE_MIN)
		return (1);
	g->win_w = ref_w * g->tile;
	g->win_h = ref_h * g->tile;
	return (0);
}

static void	copy_scaled(t_scale *sc, int tile)
{
	int	x;
	int	y;
	int	sx;
	int	sy;

	y = 0;
	while (y < tile)
	{
		sy = (int)(y * sc->ratio_y + 0.5);
		x = 0;
		while (x < tile)
		{
			sx = (int)(x * sc->ratio_x + 0.5);
			*(unsigned int *)(sc->dst + y * sc->line_size_d + x
					* sc->bits_per_pxl_d)
				= *(unsigned int *)(sc->src + sy * sc->line_size_s + sx
					* sc->bits_per_pxl_s);
			x++;
		}
		y++;
	}
}

void	*scale_xpm(void *mlx, const char *file, int tile)
{
	void	*src_img;
	void	*dst_img;
	int		w;
	int		h;
	t_scale	s;

	src_img = mlx_xpm_file_to_image(mlx, (char *)file, &w, &h);
	if (!src_img || (w == tile && h == tile))
		return (src_img);
	dst_img = mlx_new_image(mlx, tile, tile);
	s.src = mlx_get_data_addr(src_img, &s.bits_per_pxl_s,
			&s.line_size_s, &(int){0});
	s.dst = mlx_get_data_addr(dst_img, &s.bits_per_pxl_d,
			&s.line_size_d, &(int){0});
	s.bits_per_pxl_s /= 8;
	s.bits_per_pxl_d /= 8;
	s.ratio_x = (double)w / tile;
	s.ratio_y = (double)h / tile;
	copy_scaled(&s, tile);
	mlx_destroy_image(mlx, src_img);
	return (dst_img);
}

void	load_tex(t_game *g, int id, const char *file)
{
	g->tex[id] = scale_xpm(g->mlx, file, g->tile);
	if (!g->tex[id])
		error_exit(g, "Textures fails");
}

int	window_setup(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx || choose_tile(g))
		return (1);
	ft_printf("screen W = | %d | || win W | %d |\n", g->screen_w, g->win_w);
	ft_printf("screen H = | %d | || win H | %d |\n", g->screen_h, g->win_h);
	if (g->win_h > g->screen_h || g->win_w > g->screen_w)
	{
		ft_printf("Error\nMap is larger than screen.\n");
		close_window(g);
		return (1);
	}
	g->win = mlx_new_window(g->mlx,
			g->win_w,
			g->win_h,
			"so_long");
	return (!g->win);
}
