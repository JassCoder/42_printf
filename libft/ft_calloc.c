/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 13:28:31 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/14 16:43:25 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*temp;
	size_t			i;
	size_t			total;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > ULONG_MAX / size)
		return (NULL);
	total = nmemb * size;
	temp = malloc(total);
	if (!temp)
		return (NULL);
	i = 0;
	while (i < total)
	{
		temp[i] = 0;
		i++;
	}
	return (temp);
}
