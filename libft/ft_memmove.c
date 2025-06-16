/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:43:49 by erpascua          #+#    #+#             */
/*   Updated: 2025/05/02 10:48:30 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*p_dest;
	const unsigned char	*p_src;

	if (!dest && !src)
		return (NULL);
	if (dest == src || n == 0)
		return (dest);
	p_dest = (unsigned char *) dest;
	p_src = (const unsigned char *) src;
	if (p_dest > p_src)
		while (n--)
			p_dest[n] = p_src[n];
	else
	{
		i = 0;
		while (i < n)
		{
			p_dest[i] = p_src[i];
			i++;
		}
	}
	return (dest);
}
// #include <stdio.h>
// #include <string.h>
// int main(int ac, char **av)
// {
// 	(void) ac;
// 	ft_memmove(av[1], &av[1][5], 6);
// 	printf("ft_memmove\ndest : %s\n", av[1]);
// 	memmove(av[1], &av[1][5], 6);
// 	printf("memmove\ndest : %s\n\n\n", av[1]);
// 	ft_memmove(&av[1][5], av[1], 6);
// 	printf("ft_memmove\ndest : %s\n", av[1]);
// 	memmove(&av[1][5], av[1], 6);
// 	printf("memmove\ndest : %s\n\n", av[1]);
// }
