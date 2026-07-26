/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 14:54:15 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/14 16:43:54 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_len(long nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		count++;
	}
	while (nb > 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

static void	ft_handle_negative(int *n, int *is_negative)
{
	if (*n < 0)
	{
		*is_negative = 1;
		*n = -*n;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		is_negative;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_num_len(n);
	is_negative = 0;
	ft_handle_negative(&n, &is_negative);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > is_negative)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	if (is_negative)
		str[0] = '-';
	return (str);
}

/*#include "libft.h"
#include <stdio.h>

int main(void)
{
    char *s;

    s = ft_itoa(42);
    printf("%s\n", s);
    free(s);

    s = ft_itoa(-42);
    printf("%s\n", s);
    free(s);

    s = ft_itoa(0);
    printf("%s\n", s);
    free(s);

    s = ft_itoa(2147483647);
    printf("%s\n", s);
    free(s);

    s = ft_itoa(-2147483648);
    printf("%s\n", s);
    free(s);

    return (0);
}*/