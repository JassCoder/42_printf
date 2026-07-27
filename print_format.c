/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 01:27:56 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/27 16:32:57 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_str(char *str)
{
	if (str == NULL)
		return (write(1, "(null)", 6));
	return (print_str(str));
}

int	print_format(char specifier, va_list args)
{
	int		count;

	count = 0;
	if (specifier == 'c')
		count += print_char(va_arg(args, int));
	else if (specifier == 's')
		count += handle_str(va_arg(args, char *));
	else if (specifier == 'd' || specifier == 'i')
		count += print_digit((long)(va_arg(args, int)), 10);
	else if (specifier == 'x')
		count += print_digit((long)(va_arg(args, unsigned int)), 16);
	else if (specifier == 'X')
		count += print_digit_upper((long)(va_arg(args, unsigned int)), 16);
	else if (specifier == 'u')
		count += print_unsigned(va_arg(args, unsigned int));
	else if (specifier == 'p')
		count += print_pointer(va_arg(args, void *));
	else if (specifier == '%')
		count += write(1, "%", 1);
	else
		count += write(1, &specifier, 1);
	return (count);
}
