/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 04:35:32 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/14 16:44:34 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src;
	unsigned char	check;
	size_t			i;

	src = (unsigned char *)s;
	check = (unsigned char )c;
	i = 0;
	while (i < n)
	{
		if (src[i] == check)
		{
			return ((char *)s + i);
		}
		i++;
	}
	return (NULL);
}
