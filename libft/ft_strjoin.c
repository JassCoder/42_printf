/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 23:18:36 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/14 16:45:25 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		total_len;
	char		*joined;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	joined = malloc(total_len + 1);
	if (!joined)
		return (NULL);
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		joined[i + j] = s2[j];
		j++;
	}
	joined[i + j] = '\0';
	return (joined);
}
/*
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    char *result;
    
    // Test 1: Normal strings
    printf("Test 1: Normal strings\n");
    result = ft_strjoin("Hello, ", "World!");
    printf("Result: \"%s\"\n", result);
    free(result);
    printf("\n");
    
    // Test 2: Empty strings
    printf("Test 2: Empty strings\n");
    result = ft_strjoin("", "test");
    printf("Result: \"%s\"\n", result);
    free(result);
    
    result = ft_strjoin("test", "");
    printf("Result: \"%s\"\n", result);
    free(result);
    
    result = ft_strjoin("", "");
    printf("Result: \"%s\"\n", result);
    free(result);
    printf("\n");
    
    // Test 3: Different lengths
    printf("Test 3: Different lengths\n");
    result = ft_strjoin("abc", "defgh");
    printf("Result: \"%s\"\n", result);
    free(result);
    printf("\n");
    
    // Test 4: Special characters
    printf("Test 4: Special characters\n");
    result = ft_strjoin("Hello\n", "World\t!");
    printf("Result: \"%s\"\n", result);
    free(result);
    printf("\n");
    
    // Test 5: NULL input
    printf("Test 5: NULL input\n");
    result = ft_strjoin(NULL, "test");
    if (result == NULL)
        printf("Correctly returned NULL for NULL input\n");
    free(result);
    
    result = ft_strjoin("test", NULL);
    if (result == NULL)
        printf("Correctly returned NULL for NULL input\n");
    free(result);
    
    return (0);
}*/