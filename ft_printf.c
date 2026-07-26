/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 19:06:29 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/27 01:14:21 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	
	va_start(args, format);
	count = 0;
	while (*format != '\0')
	{
		if (*format == '%')
			count += print_format(*(++format), args);
		else
			count += write(1, format, 1);
		++format;
	}
	va_end(args);
	return (count);
}

// int main()
// {
// 	// int count = ft_printf("hello %s\n", "JAS");
// 	// ft_printf("hello %d\n", count);
// 	int count = ft_printf("hello %x\n", 0);
// 	ft_printf("hello %d\n", count);
// 	count = printf("hello %x\n", 0);
// 	printf("hello %d\n", count);

// 	return (0);
// }