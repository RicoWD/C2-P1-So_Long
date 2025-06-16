/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:39:12 by erpascua          #+#    #+#             */
/*   Updated: 2025/04/28 16:40:36 by erpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ptr;

	ptr = (char *) s;
	while (n > 0)
	{
		*ptr = (char) c;
		ptr++;
		n--;
	}
	return (s);
}
/*
#include <stdio.h>

int	main(void)
{
	char	str[20];
	size_t	count;

	count = 10;
	ft_memset(str, 'c', count);
	printf("%s\n", str);
}
*/
