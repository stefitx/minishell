/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 13:41:52 by pfontenl          #+#    #+#             */
/*   Updated: 2024/04/19 19:36:50 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

t_pipe_token	*create_pipe_token(void)
{
	t_pipe_token	*token;
	int				fds[2];

	token = ft_calloc(1, sizeof(t_pipe_token));
	if (!token)
		return (NULL);
	// pipe(fds);
	token->fd_in = fds[0];
	token->fd_out = fds[1];
	token->next = NULL;
	return (token);
}

t_pipe_token	*clone_pipe_token(t_pipe_token *token)
{
	t_pipe_token	*new;

	new = ft_calloc(1, sizeof(t_pipe_token));
	if (!new)
		return (NULL);
	new->fd_in = token->fd_in;
	new->fd_out = token->fd_out;
	new->next = NULL;
	return (new);
}

t_pipe_token	*find_last_pipe_token(t_pipe_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	add_pipe_token(t_pipe_token **head, t_pipe_token *new)
{
	if (!*head)
		*head = new;
	else
		find_last_pipe_token(*head)->next = new;
}

void	clear_pipe_token_list(t_pipe_token *head)
{
	if (!head)
		return ;
	clear_pipe_token_list(head->next);
	free(head);
}
