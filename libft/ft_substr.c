/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 21:01:30 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/14 16:46:01 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		slen;
	size_t		clen;
	char		*substr;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (start + len > slen)
		clen = slen - start;
	else
		clen = len;
	substr = malloc(clen + 1);
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, clen + 1);
	return (substr);
}

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	char	*result;

	// Test 1: Normal case
	result = ft_substr("Hello World", 0, 5);
	printf("Test 1: \"%s\"\n", result);
	free(result);

	// Test 2: Starting from middle
	result = ft_substr("Hello World", 6, 5);
	printf("Test 2: \"%s\"\n", result);
	free(result);

	// Test 3: Start at 0, len less than string
	result = ft_substr("Hello World", 0, 3);
	printf("Test 3: \"%s\"\n", result);
	free(result);

	// Test 4: len larger than remaining
	result = ft_substr("Hello World", 6, 20);
	printf("Test 4: \"%s\"\n", result);
	free(result);

	// Test 5: start beyond string
	result = ft_substr("Hello", 10, 5);
	printf("Test 5: \"%s\"\n", result);
	free(result);

	// Test 6: start at end of string
	result = ft_substr("Hello", 5, 5);
	printf("Test 6: \"%s\"\n", result);
	free(result);

	// Test 7: len = 0
	result = ft_substr("Hello World", 0, 0);
	printf("Test 7: \"%s\"\n", result);
	free(result);

	// Test 8: Empty string
	result = ft_substr("", 0, 5);
	printf("Test 8: \"%s\"\n", result);
	free(result);

	// Test 9: NULL string (should return NULL)
	result = ft_substr(NULL, 0, 5);
	if (result == NULL)
		printf("Test 9: NULL (correct)\n");
	else
		printf("Test 9: %s (WRONG!)\n", result);

	// Test 10: Normal case with start > 0
	result = ft_substr("Hello World", 2, 4);
	printf("Test 10: \"%s\"\n", result);
	free(result);

	return (0);
}*/