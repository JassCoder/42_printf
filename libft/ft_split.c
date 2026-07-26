/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 23:11:48 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/14 16:45:09 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_token(char	const *s, char c)
{
	size_t	in_word;
	size_t	i;
	size_t	token;

	in_word = 0;
	token = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && in_word == 0)
		{
			in_word = 1;
			token++;
		}
		else if (s[i] == c)
		{
			in_word = 0;
		}
		i++;
	}
	return (token);
}

static int	char_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && (s[len] != c))
	{
		len++;
	}
	return (len);
}

static void	free_space(char **array, int i)
{
	while (i >= 0)
	{
		free(array[i]);
		i--;
	}
	free(array);
}

static char	**fill_array(char const *s, char c, char **array, size_t token)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (i < token)
	{
		while (*s == c)
			s++;
		len = char_len(s, c);
		array[i] = malloc(len + 1);
		if (!array[i])
		{
			free_space(array, i - 1);
			return (NULL);
		}
		ft_strlcpy(array[i], s, (len + 1));
		s += len;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	token;

	if (!s)
		return (NULL);
	token = count_token(s, c);
	array = malloc((token + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	return (fill_array(s, c, array, token));
}

/*#include <stdio.h>   // ← ADD THIS!

int main(void) 
{
	char str[] = "my name is hello";
	char **container = ft_split(str, ' ');
	int i = 0;
	
	if (!container)
	{
		printf("Allocation failed!\n");
		return (1);
	}
	
	// Print all strings
	while (container[i])
	{
		printf("container[%d] = %s\n", i, container[i]);
		i++;
	}
	
	// Free all allocated memory
	i = 0;
	while (container[i])
	{
		free(container[i]);
		i++;
	}
	free(container);
	
	return (0);
}*/