/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:35:05 by pfontenl          #+#    #+#             */
/*   Updated: 2024/03/28 12:19:46 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_single_cmd	*create_single_cmd(t_text_token *args, t_redir_token *redirs)
{
	t_single_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_single_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = args;
	cmd->redirs = redirs;
	cmd->next = NULL;
	return (cmd);
}

t_single_cmd	*find_last_single_cmd(t_single_cmd *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

size_t	cmd_list_len(t_single_cmd *head)
{
	size_t	n;

	n = 0;
	while (head)
	{
		n++;
		head = head->next;
	}
	return (n);
}

void	add_single_cmd(t_single_cmd **head, t_text_token *args,
		t_redir_token *redirs)
{
	t_single_cmd	*new;

	new = create_single_cmd(args, redirs);
	if (!*head)
		*head = new;
	else
		find_last_single_cmd(*head)->next = new;
}

void	clear_single_cmd_list(t_single_cmd *head)
{
	if (!head)
		return ;
	clear_single_cmd_list(head->next);
	text_token_list_clear(head->args);
	redir_token_list_clear(head->redirs);
	free(head);
}
