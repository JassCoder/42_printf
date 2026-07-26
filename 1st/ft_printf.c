/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 13:51:15 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/26 14:15:44 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_conversion(va_list *args, char specifier)
{
	if (specifier == 'c')
		return (ft_print_char(va_arg(*args, int)));
	else if (specifier == 's')
		return (ft_print_string(va_arg(*args, char *)));
	else if (specifier == 'p')
		return (ft_print_pointer(va_arg(*args, void *)));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_print_int(va_arg(*args, int)));
	else if (specifier == 'u')
		return (ft_print_unsigned(va_arg(*args, unsigned int)));
	else if (specifier == 'x' || specifier == 'X')
		return (ft_print_hex(va_arg(*args, unsigned int), specifier));
	else if (specifier == '%')
		return (ft_print_percent());
	else
	{
		write(1, "%", 1);
		write(1, &specifier, 1);
		return (2);
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		printed;
	int		i;

	if (!format)
		return (-1);
	va_start(args, format);
	printed = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			printed += handle_conversion(&args, format[i]);
		}
		else
		{
			write(1, &format[i], 1);
			printed++;
		}
		i++;
	}
	va_end(args);
	return (printed);
}
