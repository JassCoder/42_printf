/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsingh <jsingh@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 11:51:47 by jsingh            #+#    #+#             */
/*   Updated: 2026/07/14 18:15:41 by jsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

// #include <stdio.h>
// int main()
// {
// 	t_list	*lst = NULL;

// 	t_list	*node1, *node2, *node3;

// 	node1 = ft_lstnew("first-worlds");
// 	node2 = ft_lstnew("second-worlds");
// 	node3 = ft_lstnew("third-worlds");

// 	ft_lstadd_back(&lst, node1);
// 	// now list is node1 > null;
// 	ft_lstadd_back(&lst, node2);
// 	// now list is node1 > node2 > null;
// 	ft_lstadd_back(&lst, node3);
// 	// now list is node1 > node2 > node3 > null;

// 	t_list *current = lst;
// 	while (current)
// 	{
// 		printf("%s ", (char *)current->content);
// 		current =current->next;
// 	}
// 	printf("\n");

// 	free(node1);
// 	free(node2);
// 	free(node3);
// 	return (0);
// }