/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 19:06:42 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/27 16:40:06 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <limits.h>

int	ft_printf(const char *format, ...);
int	print_format(char specifier, va_list args);
int	print_char(int c);
int	print_str(char *str);
int	print_digit(long n, int base);
int	print_digit_upper(long n, int base);
int	print_unsigned(unsigned int n);
int	print_hex_long(unsigned long n);
int	print_pointer(void *ptr);

#endif
