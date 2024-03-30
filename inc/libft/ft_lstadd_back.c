/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:21:10 by atudor            #+#    #+#             */
/*   Updated: 2023/09/29 22:36:44 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last_node = ft_lstlast(*lst);
		last_node->next = new;
	}
}

/*int main()
{
	int data1 = 42;
	t_list *node1 = ft_lstnew(&data1);
	int data2 = 69;
	t_list *node2 = ft_lstnew(&data2);
	ft_lstadd_back(&node1, node2);

	t_list *ptr = node1;
	while (ptr)
	{
		printf("%d\n", *(int *)ptr->content);
		t_list *temp = ptr->next;
		free(ptr);
		ptr = temp;
	}
	return 0;
}*/
