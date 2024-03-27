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

t_ref_token	*create_ref_token(enum e_ref_token_types type, void *data)
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

t_ref_token	*find_last_ref_token(t_ref_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	add_ref_token(t_ref_token **head, enum e_ref_token_types type,
		void *data)
{
	t_ref_token	*new;

	new = create_ref_token(type, data);
	if (!*head)
		*head = new;
	else
		find_last_ref_token(*head)->next = new;
}

void	clear_ref_token_list(t_ref_token *head)
{
	if (!head)
		return ;
	clear_ref_token_list(head->next);
	if (head->token_type == REF_TOKEN_TEXT)
		clear_text_token_list(head->text_token);
	else if (head->token_type == REF_TOKEN_REDIR)
		clear_redir_token_list(head->redir_token);
	else
		clear_pipe_token_list(head->pipe_token);
	free(head);
}
