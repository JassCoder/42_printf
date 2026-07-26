/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 20:37:27 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/14 16:45:57 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_in_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;
	size_t		i;
	char		*trimmed;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (start < end && check_in_set(s1[start], set))
		start++;
	while (end > start && check_in_set(s1[end - 1], set))
		end--;
	trimmed = malloc((end - start) + 1);
	if (!trimmed)
		return (NULL);
	i = 0;
	while (start < end)
	{
		trimmed[i] = s1[start];
		i++;
		start++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}
/*
#include <stdio.h>
int main(void)
{
    char *result;
    
    result = ft_strtrim("   Hello World   ", " ");
    printf("'%s'\n", result); // "'Hello World'"
    free(result);
    
    result = ft_strtrim("xxxabcxxxdefxxx", "x");
    printf("'%s'\n", result); // "'abcxxxdef'"
    free(result);
    
    result = ft_strtrim("abc", "abc");
    printf("'%s'\n", result); // "''"
    free(result);
    
    result = ft_strtrim("", "abc");
    printf("'%s'\n", result); // "''"
    free(result);
    
    return (0);
}*/
