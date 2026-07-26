/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 11:23:34 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/14 18:16:08 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	counter;

	counter = 0;
	while (lst != NULL)
	{
		counter++;
		lst = lst->next;
	}
	return (counter);
}

// #include <stdio.h>
// int main()
// {
// 	t_list *list = NULL;
// 	t_list *first = ft_lstnew("1st");
// 	t_list *second = ft_lstnew("2nd");
// 	t_list *third = ft_lstnew("3rd");

// 	ft_lstadd_back(&list , first);
// 	ft_lstadd_back(&list , second);
// 	ft_lstadd_back(&list , third);

// 	int size = ft_lstsize(list);
// 	printf("%d", size);

// 	free(first);
// 	free(second);
// 	free(third);
// 	return (0);

// }
