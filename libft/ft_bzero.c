/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:35:14 by erpascua          #+#    #+#             */
/*   Updated: 2025/04/28 16:40:51 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;

	str = (char *) s;
	while (n > 0)
	{
		*str = 0;
		str++;
		n--;
	}
}
/*
#include <stdio.h>

int	main(void)
{
	char	str[20];
	size_t	n;

	n = 10;
	ft_bzero(str, n);
	printf("%s\n", str);
}
*/
