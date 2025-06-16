/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:52:38 by erpascua          #+#    #+#             */
/*   Updated: 2025/05/06 15:52:57 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p_s;

	p_s = (unsigned char *)s;
	while (n > 0)
	{
		if (*p_s == (unsigned char)c)
			return (p_s);
		p_s++;
		n--;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(int ac, char **av)
{
	char	*s1;
	char	*s2;
	
	s1 = av[1];
	s2 = av[1];
	if (ac == 4)
	{
		memchr(s2, ft_atoi(av[2]), ft_atoi(av[3]));
		printf("memchr    || %s\n", s2);
		ft_memchr(s1, ft_atoi(av[2]), ft_atoi(av[3]));
		printf("ft_memchr || %s\n", s1);
	}
}
*/