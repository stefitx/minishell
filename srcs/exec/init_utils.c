/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:16:23 by atudor            #+#    #+#             */
/*   Updated: 2024/04/09 15:16:26 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_cmds(t_command *cmd)
{
	int				nr_cmds;
	t_single_cmd	*cursor;

	nr_cmds = 0;
	cursor = cmd->cmd_list;
	while (cursor)
	{
		nr_cmds++;
		cursor = cursor->next;
	}
	return (nr_cmds);
}

void	count_redirs(t_xcmd *xcmd, t_redir_token *parse_redir)
{
	t_redir_token	*temp;

	xcmd->nr_redir_in = 0;
	xcmd->nr_redir_out = 0;
	xcmd->nr_heredoc = 0;
	xcmd->nr_append = 0;
	temp = parse_redir;
	while (temp)
	{
		if (temp->redir_type == REDIR_INFILE)
			xcmd->nr_redir_in++;
		else if (temp->redir_type == REDIR_OUTFILE)
			xcmd->nr_redir_out++;
		else if (temp->redir_type == REDIR_HEREDOC)
			xcmd->nr_heredoc++;
		else if (temp->redir_type == REDIR_APPEND)
			xcmd->nr_append++;
	}
}

int	check_builtin(char **xcmd)
{
	if (ft_strcmp(xcmd[0], "cd") || ft_strcmp(xcmd[0], "pwd")
		|| ft_strcmp(xcmd[0], "echo") || ft_strcmp(xcmd[0], "export")
		|| ft_strcmp(xcmd[0], "unset") || ft_strcmp(xcmd[0], "env"))
		return (1);
	else
		return (0);
}
