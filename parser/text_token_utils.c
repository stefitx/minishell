/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:41:52 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/17 14:05:48 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_text_token	*create_text_token(char *original, char *original_quoted,
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

t_text_token	*clone_text_token(t_text_token *token)
{
	if (!token)
		return (NULL);
	return create_text_token(token->original, token->original_quoted,
		token->expanded, token->in_quotes);
}

t_text_token	*find_last_text_token(t_text_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	add_text_token(t_text_token **head, t_text_token *new)
{
	if (!*head)
		*head = new;
	else
		find_last_text_token(*head)->next = new;
}

void	clear_text_token_list(t_text_token *head)
{
	if (!head)
		return ;
	clear_text_token_list(head->next);
	free(head->original);
	free(head->original_quoted);
	free(head);
}
