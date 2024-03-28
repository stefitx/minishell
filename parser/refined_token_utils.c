/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_token_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:41:52 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/17 13:21:32 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ref_token	*ref_token_create(enum e_ref_token_types type, void *data)
{
	t_ref_token	*token;

	token = ft_calloc(1, sizeof(t_ref_token));
	if (!token)
		return (NULL);
	token->token_type = type;
	if (type == REF_TOKEN_TEXT)
		token->text_token = data;
	else if (type == REF_TOKEN_REDIR)
		token->redir_token = data;
	else
		token->pipe_token = data;
	token->next = NULL;
	return (token);
}

t_ref_token	*ref_token_find_last(t_ref_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	ref_token_append(t_ref_token **head, enum e_ref_token_types type,
		void *data)
{
	t_ref_token	*new;

	new = ref_token_create(type, data);
	if (!*head)
		*head = new;
	else
		ref_token_find_last(*head)->next = new;
}

void	ref_token_list_clear(t_ref_token *head)
{
	if (!head)
		return ;
	ref_token_list_clear(head->next);
	if (head->token_type == REF_TOKEN_TEXT)
		text_token_list_clear(head->text_token);
	else if (head->token_type == REF_TOKEN_REDIR)
		redir_token_list_clear(head->redir_token);
	else
		clear_pipe_token_list(head->pipe_token);
	free(head);
}
