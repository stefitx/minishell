/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:47:51 by atudor            #+#    #+#             */
/*   Updated: 2023/09/29 22:19:59 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

/* ok so what this function does: it needs a pointer to the first node of 
 * the
 * list, bc it only works with adding a node at the front, and if both the nodes
 * are alright it takes the new node, accesses its own internal pointer that it 
 * has 
 * (that rn points to null, as we have defined it in the struct, and it makes it
 * point to lst which is the first pointer in the list. basically we r playing
 * with how the lists are linked, if u link a node to the first node in the
 * list, that one becomes the new pointer.
 * then, we go to the pointer that we had previously as an argument, that points
 * to the head of the list, and we make it point to the current head of the
 * list, which is "new"*/

/*int main()
{
	int data1 = 42;
	t_list *node1 = ft_lstnew(&data1);
	int data2 = 69;
	t_list *node2 = ft_lstnew(&data2);
	ft_lstadd_front(&node1, node2);

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

/* basically u create the two nodes that are linked, with the integers inside, 
then you pass the function with an ampersand @ the first one because as u can see
 * the first argument is a double pointer (a node already contains a pointer),
 * then you make a pointer that starts at the first node, points to the content
 * (we cast the pointer as the content is an int so our pointer becomes an int
 * pointer) does printf of the content and then passes onto the next node.*/
