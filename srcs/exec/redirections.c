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

int	eval_heredoc(char *limiter)
{
	int		heredoc_fd[2];
	char	*line;

	pipe_error(heredoc_fd);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		write(heredoc_fd[1], line, ft_strlen(line));
		write(heredoc_fd[1], "\n", 1);
		free(line);
	}
	return (heredoc_fd[0]);
}

void	out_redir(t_xcmd *cmd)
{
	int	i;

	i = 0;
	printf("outfile: %s\n", cmd->outfile[i]);
	while (i < cmd->nr_redir_out)
	{
		if (cmd->outfile[i][0] == '\n')
		{
			cmd->outfile[i] = ft_strtrim(cmd->infile[i], " \n");
			cmd->fd_out = open(cmd->outfile[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else
			cmd->fd_out = open(cmd->outfile[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fd_out < 0)
		{
			perror(cmd->outfile[i]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	dup2(cmd->fd_out, STDOUT_FILENO);
	close(cmd->fd_out);
}

void	in_redir(t_xcmd *cmd)
{
	int	i;

	i = 0;
	printf("infile: %s\n", cmd->infile[i]);
	while (cmd->infile[i] != NULL && i < cmd->nr_redir_in)
	{
		if (cmd->infile[i][0] == '\n')
		{
			cmd->infile[i] = ft_strtrim(cmd->infile[i], " \n");
			cmd->fd_in = eval_heredoc(cmd->infile[i]);
		}
		else
			cmd->fd_in = open(cmd->infile[i], O_RDONLY);
		if (cmd->fd_in < 0)
		{
			perror(cmd->infile[i]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	dup2(cmd->fd_in, STDIN_FILENO);
	close(cmd->fd_in);
}

void	pipe_redir(t_xcmd **cmd, int i)
{
	if (cmd[i]->nr_cmds > 1)
	{
		if (cmd[i]->cmd_id == 0)
		{
			dup2(cmd[i]->pipefd[1], 1);
			close(cmd[i]->pipefd[1]);
			printf("pipefd[1]: %d\n", cmd[i]->pipefd[1]);
			close(cmd[i]->pipefd[0]);
		}
		else if (cmd[i]->cmd_id > 0)
		{
			dup2(cmd[i - 1]->pipefd[0], 0);
			close(cmd[i -1]->pipefd[0]);
			printf("pipefd[0]: %d\n", cmd[i - 1]->pipefd[0]);
			close(cmd[i]->pipefd[1]);
			if (i < cmd[i]->nr_cmds - 1)
			{
				dup2(cmd[i]->pipefd[1], 1);
				close(cmd[i]->pipefd[0]);
				close(cmd[i]->pipefd[1]);
			}
		}

	}
}

void	redirections(t_xcmd ***cmd, int i)
{
	pipe_redir(*cmd, i);
	if ((*cmd)[i]->nr_redir_in > 0)
	{
		in_redir(*cmd[i]);
	}
	if ((*cmd)[i]->nr_redir_out > 0)
	{
		out_redir(*cmd[i]);
	}
}
