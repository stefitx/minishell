/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:05:15 by atudor            #+#    #+#             */
/*   Updated: 2023/09/29 20:13:24 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

/*u have a pointer to the head of the list. it is a node bc it has a next in it.
 * u make it go through the "next" and get to the next node, until the "next"
 * points to null. u increase i as many times as there is somewhere to go. u
 * should prolly add one for the null if ur gonna use it ever.*/
