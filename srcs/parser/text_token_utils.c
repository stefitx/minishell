/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:41:52 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/19 19:36:50 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

t_text_token	*text_token_create(char *original, char *original_quoted,
		t_str_node *expanded, int in_quotes)
{
	t_text_token	*token;

	token = ft_calloc(1, sizeof(t_text_token));
	if (!token)
		return (NULL);
	token->original = ft_strdup(original);
	token->original_quoted = ft_strdup(original_quoted);
	token->expanded = expanded;
	token->in_quotes = in_quotes;
	token->next = NULL;
	return (token);
}

t_text_token	*text_token_clone(t_text_token *token)
{
	if (!token)
		return (NULL);
	return (text_token_create(token->original, token->original_quoted,
			clone_str_node_list(token->expanded), token->in_quotes));
}

t_text_token	*text_token_find_last(t_text_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	text_token_append(t_text_token **head, t_text_token *new)
{
	if (!*head)
		*head = new;
	else
		text_token_find_last(*head)->next = new;
}

void	text_token_list_clear(t_text_token *head)
{
	if (!head)
		return ;
	text_token_list_clear(head->next);
	free(head->original);
	free(head->original_quoted);
	clear_str_node_list(head->expanded);
	free(head->expanded_full);
	free(head);
}
