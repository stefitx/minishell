/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:41:52 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/28 12:20:33 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*token_create(char *s, enum e_token_types type, char quote)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = s;
	if (type == TOKEN_REDIR && s[0] == '|')
		type = TOKEN_PIPE;
	token->token_type = type;
	if (quote == '\'')
		token->quote_status = QUOTE_SINGLE;
	if (quote == '"')
		token->quote_status = QUOTE_DOUBLE;
	else
		token->quote_status = QUOTE_NONE;
	token->next = NULL;
	return (token);
}

t_token	*token_find_last(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	token_append(t_token **head, char *s, enum e_token_types type,
		char quote)
{
	t_token	*new;

	new = token_create(s, type, quote);
	if (!*head)
		*head = new;
	else
		token_find_last(*head)->next = new;
}

void	token_list_clear(t_token *head)
{
	if (!head)
		return ;
	token_list_clear(head->next);
	free(head->content);
	free(head);
}
