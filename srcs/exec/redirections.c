/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:28:04 by atudor            #+#    #+#             */
/*   Updated: 2024/04/09 15:28:07 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	fd_error(t_xcmd *cmd, t_redir_token *temp, int fd, char c)
{
	char	*f;

	if (c == 'o')
	{
		f = temp->text_token->expanded->str;
		if (temp->redir_type == REDIR_APPEND)
			cmd->fd_o = open(f, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			cmd->fd_o = open(f, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if ((fd < 0 && c == 'i') || (c == 'o' && cmd->fd_o < 0))
	{
		write(2, "minishell: ", 11);
		perror(temp->text_token->expanded->str);
		cmd->exit_status = 1;
		if (!cmd->builtin && cmd->cmd != NULL && cmd->cmd[0] != NULL)
			exit(1);
		if (cmd->builtin)
			return (1);
	}
	return (0);
}

void	out_redir(t_xcmd *cmd)
{
	t_redir_token	*temp;

	temp = cmd->redirs;
	if (cmd->fd_o != -3)
		close(cmd->fd_o);
	while (temp && temp->text_token)
	{
		if (temp->redir_type == REDIR_OUTFILE
			|| temp->redir_type == REDIR_APPEND)
		{
			if (ambiguous_redir(temp->text_token, cmd))
				return ;
			if (temp->text_token && temp->text_token->expanded)
				if (fd_error(cmd, temp, cmd->fd_o, 'o'))
					return ;
		}
		temp = temp->next;
	}
	dup2(cmd->fd_o, STDOUT_FILENO);
	close(cmd->fd_o);
}

void	in_redir(t_xcmd *cmd)
{
	t_redir_token	*temp;

	temp = cmd->redirs;
	if (cmd->fd_in != -3)
		close(cmd->fd_in);
	while (temp && temp->text_token)
	{
		if (temp->redir_type == REDIR_INFILE)
		{
			if (ambiguous_redir(temp->text_token, cmd))
				return ;
			if (temp->text_token && temp->text_token->expanded)
			{
				cmd->fd_in = open(temp->text_token->expanded->str, O_RDONLY);
				if (fd_error(cmd, temp, cmd->fd_in, 'i'))
					return ;
			}
		}
		temp = temp->next;
	}
	dup2(cmd->fd_in, STDIN_FILENO);
	close(cmd->fd_in);
}

void	pipe_redir(t_xcmd **cmd, int i, int *flag)
{
	if (cmd[i]->nr_cmds > 1)
	{
		(*flag) = 1;
		if (cmd[i]->cmd_id == 0)
		{
			if (dup2(cmd[i]->pipefd[1], 1) == -1)
				close(cmd[i]->pipefd[1]);
		}
		else if (cmd[i]->cmd_id > 0)
		{
			if (dup2(cmd[i - 1]->pipefd[0], 0) == -1)
				close(cmd[i - 1]->pipefd[0]);
			if (i < cmd[i]->nr_cmds - 1)
			{
				if (dup2(cmd[i]->pipefd[1], 1) == -1)
					close(cmd[i]->pipefd[1]);
				if (cmd[i - 1]->cmd == NULL)
					close(cmd[i - 1]->pipefd[1]);
			}
		}
	}
}

void	redirections(t_xcmd **cmd, int i, int *flag)
{
	pipe_redir(cmd, i, flag);
	if (cmd[i]->nr_redir_in > 0)
		in_redir(cmd[i]);
	if (cmd[i]->nr_redir_out > 0)
		out_redir(cmd[i]);
}
