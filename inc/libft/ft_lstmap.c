/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 23:15:51 by atudor            #+#    #+#             */
/*   Updated: 2023/10/14 23:34:55 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr;
	t_list	*node;
	void	*content;

	if (!lst || !f)
		return (NULL);
	ptr = NULL;
	while (lst)
	{
		content = f(lst->content);
		if (content)
			node = ft_lstnew(content);
		if (!content || !node)
		{
			free(content);
			ft_lstclear(&ptr, del);
			return (NULL);
		}
		ft_lstadd_back(&ptr, node);
		lst = lst->next;
	}
	return (ptr);
}

/*t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),void (*del)(void *))
{
	t_list *new_list;
	t_list *node;
	void *content

	if (!lst || !f)
		return (NULL);
	ptr = NULL;
	while(lst)
	{
		content = f(lst->content)
		if(!content)
		{
			free(content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		node = ft_lstnew(f(lst->content));
		if(!node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, node);
		lst = lst->next;
	}
	return (new_list);
	}*/