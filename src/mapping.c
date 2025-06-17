/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:56:00 by erpascua          #+#    #+#             */
/*   Updated: 2025/06/17 19:42:56 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	is_allowed(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}


void	check_line_border(char *line, int row, int height, int width)
{
	if 
	{

	}
}

// int	map_read_conformity(char *line)
// {
// 	int	col;
// 
// 	col = 0;
// 	while (line[col] && line[col] != '\n')
// 	{
// 		if (line == 0 && line + 1 == (void *)0)
// 		{
// 			if (!(line[col] == '1' && line[col - 1] == '1'))
// 			{
// 				ft_printf("Error: char '%c' is not a '1' (wall) for the map's border.\n", col);
// 				free(line);
// 				return (0);
// 			}
// 			col++;
// 		}
// 		if (line >= '1' && line +2 <= '\0')
// 		{
// 			if (!(line[0] == '1' && line[col + 1] == '\n'))
// 			{
// 				ft_printf("Error: char '%c' is not a '1' (wall) for the map's border.\n", col);
// 				free(line);
// 				return (0);
// 			}
// 			col++;
// 		}
// 	}
// 	return (1);
// }

// void	map_read_line(char *line)
// {
// 	int	col;
// 
// 	col = 0;
// 	while (line[col] && line[col + 2] != '\n')
// 	{
// 		if (!is_allowed(col))
// 		{
// 			ft_printf("Error: char '%c' is invalid\n", col);
// 			return ;
// 		}
// 		col++;
// 	}
//		if (map_read_conformity(line))
//			ft_printf("Map is conform\n");
// }

void	treatment_map(const char *path)
{
	int		fd;
	char	*line;
	int		row;
	int		height;
	int		len;
	int		width;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror("open"), (void)0);
	height = 0;
	while ((line = get_next_line(fd)))
	{
		height++;
		free(line);
	}
	close(fd);
	ft_printf("%d\n", height);
	fd = open(path, O_RDONLY);
	width = -1;
	row = 0;
	while ((line = get_next_line(fd)))
	{
		ft_printf("%s", line);
		len = ft_strlen(line) - (line[ft_strlen(line)-1] == '\n');
		if (width == -1)
			width == len;
		else if (len != width)
			quit_error("ERROR: The map is not rectangular");
        check_line_border(line, row, height, width);
		free(line);
	}
	ft_printf("\n");
}
