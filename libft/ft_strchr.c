/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:53:56 by erpascua          #+#    #+#             */
/*   Updated: 2025/05/02 14:53:57 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}
/*
#include <stdio.h>

int	main()
{
	//if (ac == 3)
	//{
		printf("strnchr    || %s\n", ft_strchr("teste", 1024));
		//printf("strnchr    || %s\n", ft_strchr(av[1], atoi(av[2])));
		//printf("ft_strnchr || %s\n", ft_strchr(av[1], atoi(av[2])));
		printf("ft_strnchr || %s\n", ft_strchr("teste", 1024));
		//}
	}
	
*/