/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:41:52 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/19 19:36:50 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/minishell.h"

t_redir_token	*redir_token_create(enum e_redir_types type, t_text_token *data)
{
	t_redir_token	*token;

	token = ft_calloc_err(1, sizeof(t_redir_token));
	token->redir_type = type;
	token->text_token = data;
	token->next = NULL;
	return (token);
}

t_redir_token	*redir_token_clone(t_redir_token *token)
{
	if (!token)
		return (NULL);
	return (redir_token_create(token->redir_type, token->text_token));
}

t_redir_token	*redir_token_find_last(t_redir_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	redir_token_append(t_redir_token **head, t_redir_token *new)
{
	if (!*head)
		*head = new;
	else
		redir_token_find_last(*head)->next = new;
}

void	redir_token_list_clear(t_redir_token *head)
{
	if (!head)
		return ;
	redir_token_list_clear(head->next);
	text_token_list_clear(head->text_token);
	free(head);
}
