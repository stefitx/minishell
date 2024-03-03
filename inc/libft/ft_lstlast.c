/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:13:41 by atudor            #+#    #+#             */
/*   Updated: 2023/09/29 21:56:53 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;

	ptr = NULL;
	while (lst)
	{
		ptr = lst;
		lst = lst->next;
	}
	return (ptr);
}

/*int main()
{
	char *data1 = "first node";
	t_list *node1 = ft_lstnew(data1);
	
	char *data2 = "last node hehe";
	t_list *node2 = ft_lstnew(data2);
	
	node1->next = node2;
	
	t_list *last_node = ft_lstlast(node1);

	printf("%s\n", last_node->content);
	return 0;
}*/
