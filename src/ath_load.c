/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ath_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:18:20 by ubuntu            #+#    #+#             */
/*   Updated: 2025/07/03 15:13:48 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	get_ath_cols(const char *path)
{
	int		fd;
	char	*line;
	int		len;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	if (fd < 0 || !line)
		return (0);
	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	free(line);
	close(fd);
	return (len);
}

static int	get_raw_len(char *raw)
{
	int	len;

	len = 0;
	while (raw[len] && raw[len] != '\n')
		len++;
	return (len);
}

static void	fill_padded(char *padded, char *raw, int len, int win_w)
{
	int	i;

	i = 0;
	while (i < len && i < win_w)
	{
		padded[i] = raw[i];
		i++;
	}
	while (i < win_w)
		padded[i++] = 'S';
	padded[i] = '\0';
}

static char	*ath_padded_line(t_game *g)
{
	int		fd;
	char	*raw;
	char	*padded;
	int		len;

	fd = open(g->ath_path, O_RDONLY);
	if (fd < 0)
		return (close(fd), NULL);
	raw = get_next_line(fd);
	if (!raw)
		return (close(fd), NULL);
	len = get_raw_len(raw);
	padded = malloc(g->win_w + 1);
	if (!padded)
		return (free(raw), close(fd), NULL);
	fill_padded(padded, raw, len, g->win_w);
	free(raw);
	close(fd);
	return (padded);
}

void	load_ath(t_game *g)
{
	char	*line;

	line = ath_padded_line(g);
	if (!line)
		return (free(line), error_exit(g, "Issue with ATH loading"));
	draw_ath(g, line);
	free(line);
}
