/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_node_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:41:52 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/18 18:25:45 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_str_node	*create_str_node(char *s)
{
	t_str_node	*node;

	node = ft_calloc(1, sizeof(t_str_node));
	if (!node)
		return (NULL);
	node->str = ft_strdup(s);
	node->next = NULL;
	return (node);
}

t_str_node	*clone_str_node_list(t_str_node *node)
{
	t_str_node	*head;

	if (!node)
		return (NULL);
	head = create_str_node(node->str);
	head->next = clone_str_node_list(node->next);
	return (head);
}

t_str_node	*find_last_str_node(t_str_node *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	add_str_node(t_str_node **head, t_str_node *node)
{
	if (!*head)
		*head = node;
	else
		find_last_str_node(*head)->next = node;
}

void	clear_str_node_list(t_str_node *head)
{
	if (!head)
		return ;
	clear_str_node_list(head->next);
	free(head->str);
	free(head);
}
