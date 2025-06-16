/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:55:26 by erpascua          #+#    #+#             */
/*   Updated: 2025/05/02 14:55:55 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
// #include <stdio.h>

// int	main(int ac, char **av)
// {
// 	int i;
// 	int j;

//     i = 1;
//     j = 0;
//     while (i < ac)
//     {
//         while (av[i][j])
//         {
//             printf("%c > %c\n", av[i][j], ft_tolower(av[i][j]));
//             j++;
//         }
//         printf("\n\n");
//         i++;
//         j = 0;
//     }
// }