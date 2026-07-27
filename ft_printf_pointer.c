/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 16:45:53 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/27 16:47:28 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex_long(unsigned long n)
{
	int			count;
	char		*digits;

	count = 0;
	digits = "0123456789abcdef";
	if (n >= 16)
		count += print_hex_long(n / 16);
	count += write(1, &digits[n % 16], 1);
	return (count);
}

int	print_pointer(void *ptr)
{
	int					count;
	unsigned long		address;

	count = 0;
	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	address = (unsigned long)ptr;
	count += write(1, "0x", 2);
	count += print_hex_long(address);
	return (count);
}
