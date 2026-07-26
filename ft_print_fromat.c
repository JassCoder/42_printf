/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fromat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 01:27:56 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/27 01:29:27 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format(char specifier, va_list args)
{
	int		count;
	char	*str;

	count = 0;
	if (specifier == 'c')
		count += print_char(va_arg(args, int));
	else if (specifier == 's')
	{
		str = va_arg(args, char *);
		if (str == NULL)
			count += write(1, "(null)", 6);
		else
			count += print_str(str);
	}
	else if (specifier == 'd')
		count += print_digit((long)(va_arg(args, int)), 10);
	else if (specifier == 'x')
		count += print_digit((long)(va_arg(args, unsigned int)), 16);
	else
		count += write(1, &specifier, 1);
	return (count);
}
