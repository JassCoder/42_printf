/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 19:57:16 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/14 16:45:40 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char		*result;
	size_t		len;
	size_t		index;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	index = 0;
	while (index < len)
	{
		result[index] = f(index, s[index]);
		index++;
	}
	result[index] = '\0';
	return (result);
}

/*#include <stdio.h>
#include <stdlib.h>

char	to_upper(unsigned int i, char c)
{
	(void)i;
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

char	add_index(unsigned int i, char c)
{
	return (c + i);
}

char	alternate_case(unsigned int i, char c)
{
	if (i % 2 == 0)
	{
		if (c >= 'a' && c <= 'z')
			return (c - 32);
	}
	else
	{
		if (c >= 'A' && c <= 'Z')
			return (c + 32);
	}
	return (c);
}

int	main(void)
{
	char	*result;

	// Test 1: Uppercase
	result = ft_strmapi("hello", to_upper);
	printf("Uppercase: %s\n", result);  // "HELLO"
	free(result);

	// Test 2: Add index
	result = ft_strmapi("abc", add_index);
	printf("Add index: %s\n", result);  // "ace"
	free(result);

	// Test 3: Alternate case
	result = ft_strmapi("hello world", alternate_case);
	printf("Alternate: %s\n", result);  // "HeLlO WoRlD"
	free(result);

	// Test 4: Empty string
	result = ft_strmapi("", to_upper);
	printf("Empty: %s\n", result);  // ""
	free(result);

	// Test 5: NULL
	result = ft_strmapi(NULL, to_upper);
	printf("NULL: %s\n", result ? result : "NULL");  // NULL

	return (0);
}*/