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

int	ambiguous_redir(t_text_token *redir, t_xcmd *cmd)
{
	int	i;
	t_text_token	*temp;
	t_str_node		*temp2;

	i = 0;
	temp = redir;
	temp2 = temp->expanded;
	while (temp2)
	{
		if (temp2->str)
			i++;
		temp2 = temp2->next;
	}
	if (i != 1 || redir->expanded->str == NULL)
	{
		write(2, "minishell: ", 11);
		write(2, "ambiguous redirect\n", 19);
		cmd->exit_status = 1;
		if (!cmd->builtin)
			exit(1);
		return (1);
	}
	return (0);
}

void	out_redir(t_xcmd *cmd)
{
	t_redir_token	*temp;

	temp = cmd->redirs;
	while (temp && temp->text_token)
	{
		if (temp->redir_type == REDIR_OUTFILE || temp->redir_type == REDIR_APPEND)
		{
			if (ambiguous_redir(temp->text_token, cmd))
				return ;
			if (temp->text_token && temp->text_token->expanded)
			{
				if (temp->redir_type == REDIR_APPEND)
					cmd->fd_o = open(temp->text_token->expanded->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
				else
					cmd->fd_o = open(temp->text_token->expanded->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (cmd->fd_o < 0)
				{
					write(2, "minishell: ", 11);
					perror(temp->text_token->expanded->str);
					cmd->exit_status = 1;
					if (!cmd->builtin)
						exit(1);
					if (cmd->builtin)
						return ;
				}
			}
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
	while (temp && temp->text_token)
	{
		if (temp->redir_type == REDIR_INFILE)
		{
			if (ambiguous_redir(temp->text_token, cmd))
				return ;
			if (temp->text_token && temp->text_token->expanded)
			{
				cmd->fd_in = open(temp->text_token->expanded->str, O_RDONLY);
				if (cmd->fd_in < 0)
				{
					write(2, "minishell: ", 11);
					perror(temp->text_token->expanded->str);
					cmd->exit_status = 1;
					if (!cmd->builtin)
						exit(1);
					if (cmd->builtin)
						return ;
				}
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
			dup2(cmd[i]->pipefd[1], 1);
			close(cmd[i]->pipefd[1]);
			close(cmd[i]->pipefd[0]);
		}
		else if (cmd[i]->cmd_id > 0)
		{
			dup2(cmd[i - 1]->pipefd[0], 0);
			close(cmd[i - 1]->pipefd[0]);
			close(cmd[i]->pipefd[0]);
			if (i < cmd[i]->nr_cmds - 1)
			{
				dup2(cmd[i]->pipefd[1], 1);
				close(cmd[i]->pipefd[1]);
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
