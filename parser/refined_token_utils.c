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

t_ref_token	*create_ref_token(enum e_ref_token_types type,
		void *data)
{
	t_ref_token	*token;

	token = ft_calloc(1, sizeof(t_ref_token));
	if (!token)
		return (NULL);
	token->token_type = type;
	if (type == R_Text)
		token->text_token = data;
	else if (type == R_Redir)
		token->redir_token = data;
	else if (type == R_Pipe)
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

void	add_ref_token(t_ref_token **head,
		enum e_ref_token_types type, void *data)
{
	t_ref_token	*new;

	new = create_ref_token(type, data);
	if (!*head)
		*head = new;
	else
		find_last_ref_token(*head)->next = new;
}
