/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 11:48:08 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/14 18:16:50 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

// #include<stdio.h>
// int	main()
// {
// 	t_list	*lst = NULL;
// 	t_list	*node1, *node2 , *node3 ,*last;

// 	node1 = ft_lstnew("1st");
// 	node2 = ft_lstnew("2nd");
// 	node3 = ft_lstnew("3rd");

// 	// ft_lstadd_front(&lst , node3);
// 	// ft_lstadd_front(&lst , node2);
// 	ft_lstadd_front(&lst , node1);
// 	last = ft_lstlast(lst);

// 	printf("%s ", (char *)last->content);

// 	free(node1);
// 	free(node2);
// 	free(node3);
// 	return(0);
// }