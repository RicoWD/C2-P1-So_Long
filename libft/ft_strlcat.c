/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:54:23 by erpascua          #+#    #+#             */
/*   Updated: 2025/05/02 14:54:25 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	int		i;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (len_src);
	if (dstsize <= len_dst)
		return (len_src + dstsize);
	else
	{
		while (src[i] && (len_dst + i) < (dstsize - 1))
		{
			dst[len_dst + i] = src[i];
			i++;
		}
	}
	dst[len_dst + i] = '\0';
	return (len_src + len_dst);
}
/*
#include <stdio.h>

int	main(int ac, char **av)
{
	if (ac == 4)
	{
		printf("strlcat    || %d\n", strlcat(av[1], av[2], atoi(av[3])));
		printf("ft_strlcat || %zu\n", ft_strlcat(av[1], av[2], atoi(av[3])));
	}
}
*/