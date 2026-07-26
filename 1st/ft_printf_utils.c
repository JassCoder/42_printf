/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 14:07:56 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/26 14:10:46 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(unsigned long long n, char *base)
{
	int	base_len;
	int	count;

	base_len = ft_strlen(base);
	count = 0;
	if (n >= (unsigned long long)base_len)
		count += ft_putnbr_base(n / base_len, base);
	write(1, &base[n % base_len], 1);
	return (count + 1);
}

int	ft_count_digits(unsigned long long n, int base_len)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= base_len;
		count++;
	}
	return (count);
}

int	ft_putstr_len(char *s)
{
	int	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	write(1, s, len);
	return (len);
}
