/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:51:59 by erpascua          #+#    #+#             */
/*   Updated: 2025/05/02 14:52:04 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (size && count > 18446744073709551615UL / size)
		return (NULL);
	p = malloc (count * size);
	if (!p)
		return (NULL);
	ft_bzero(p, (count * size));
	return (p);
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	char	*r1;
	char	*r2;

	if (ac == 3)
	{
		r1 = (char *)calloc(ft_atoi(av[1]), ft_atoi(av[2]));
		printf("calloc    || %s\n", r1);
		r2 = (char *)ft_calloc(ft_atoi(av[1]), ft_atoi(av[2]));
		printf("ft_calloc || %s\n", r2);
	}
}
*/
