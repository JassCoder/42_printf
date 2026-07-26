/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 19:06:42 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/27 01:12:20 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <limits.h>


int	ft_printf(const char *, ...);

int	print_format(char specifiers, va_list args);
int	print_char(int c);
int print_str(char *str);
int	print_digit(long n, int base);

#endif