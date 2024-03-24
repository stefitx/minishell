/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:41:52 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/17 14:07:09 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir_token	*create_redir_token(enum e_redir_types type, t_text_token *data)
{
	t_redir_token	*token;

	token = ft_calloc(1, sizeof(t_redir_token));
	if (!token)
		return (NULL);
	token->redir_type = type;
	token->text_token = clone_text_token(data);
	token->next = NULL;
	return (token);
}

t_redir_token	*clone_redir_token(t_redir_token *token)
{
	if (!token)
		return (NULL);
	return create_redir_token(token->redir_type, token->text_token);
}

t_redir_token	*find_last_redir_token(t_redir_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	add_redir_token(t_redir_token **head, t_redir_token *new)
{
	if (!*head)
		*head = new;
	else
		find_last_redir_token(*head)->next = new;
}

void	clear_redir_token_list(t_redir_token *head)
{
	if (!head)
		return ;
	clear_redir_token_list(head->next);
	clear_text_token_list(head->text_token);
	free(head);
}
