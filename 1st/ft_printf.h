/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 13:51:13 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/26 14:09:11 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>      // For va_list, va_start, va_arg, va_end
# include <unistd.h>      // For write
# include <stdlib.h>      // For malloc, free
# include "libft/libft.h" // Your libft

// Main function prototype
int	ft_printf(const char *format, ...);

// Conversion functions (we'll implement these)
int	ft_print_char(int c);
int	ft_print_string(char *s);
int	ft_print_pointer(void *ptr);
int	ft_print_int(int n);
int	ft_print_unsigned(unsigned int n);
int	ft_print_hex(unsigned int n, char specifier);
int	ft_print_percent(void);

// Utility functions
int	ft_putnbr_base(unsigned long long n, char *base);
int	ft_count_digits(unsigned long long n, int base_len);

#endif