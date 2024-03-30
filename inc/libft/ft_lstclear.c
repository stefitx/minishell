/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:56:58 by atudor            #+#    #+#             */
/*   Updated: 2023/12/06 13:12:28 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*last;

	if (!lst)
		return ;
	ptr = *lst;
	while (ptr)
	{
		last = ptr;
		ptr = ptr->next;
		del(last->content);
		free(last);
	}
	*lst = NULL;
}
