/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 05:50:02 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/14 16:43:15 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	neg = 1;
	res = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res *= 10 ;
		res += nptr[i] - '0';
		i++;
	}
	return (res * neg);
}

/*#include <stdio.h>
int main(void)
{
	printf("\"42\"    → %d\n", ft_atoi("42"));
	printf("\"-42\"   → %d\n", ft_atoi("-42"));
	printf("\"+42\"   → %d\n", ft_atoi("+42"));
	printf("\"  -42\" → %d\n", ft_atoi("  -42"));
	printf("\"0\"     → %d\n", ft_atoi("0"));
	printf("\"  +0\"  → %d\n", ft_atoi("  +0"));
	printf("\"-0\"    → %d\n", ft_atoi("-0"));
	printf("\"abc\"   → %d\n", ft_atoi("abc"));
	printf("\"42abc\" → %d\n", ft_atoi("42abc"));
	printf("\"  +-42\"→ %d\n", ft_atoi("  +-42"));  // Stops at '+', returns 0
	return (0);
}*/
