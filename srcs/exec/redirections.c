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
	close(heredoc_fd[1]);
	return (heredoc_fd[0]);
}

int	ambiguous_redir(char **redir, t_xcmd *cmd)
{
	int	i;

	i = 0;
	while (redir && redir[i] != NULL)
		i++;
	if (i != 1 || redir == NULL)
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
	int	i;
	int		j;
	char	*temp;

	i = 0;
	while (i < cmd->nr_redir_out)
	{
		if (ambiguous_redir(cmd->out[i], cmd))
			return ;
		j = 0;
		// if (cmd->out)
		// 	dprintf(1, "Hola\n");
		while (cmd->out[i][j] != NULL)
		{
			if (cmd->out[i][j][0] == '\n')
			{
				temp = ft_strtrim(cmd->out[i][j], " \n");
				free(cmd->out[i][j]);
				cmd->out[i][j] = temp;
				free(temp);
				cmd->fd_o = open(cmd->out[i][j], O_WRONLY | O_CREAT | O_APPEND, 0644);
			}
			else
				cmd->fd_o = open(cmd->out[i][j], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmd->fd_o < 0)
			{
				write(2, "minishell: ", 11);
				perror(cmd->out[i][j]);
				cmd->exit_status = 1;
				if (!cmd->builtin)
					exit(1);
				if (cmd->builtin)
					return ;
			}
			j++;
		}
		i++;
	}
	dup2(cmd->fd_o, STDOUT_FILENO);
	close(cmd->fd_o);
}

void	in_redir(t_xcmd *cmd)
{
	int		i;
	int		j;
	char	*temp;
	char	**redirs;

	i = 0;
	while (i < cmd->nr_redir_in)
	{
		if (ambiguous_redir(cmd->infile[i], cmd))
			return ;
		if (cmd->infile[i] != NULL)
		{
		redirs = cmd->infile[i];
		j = 0;
		while (redirs[j] != NULL)
		{
			if (redirs[j][0] == '\n')
			{
				temp = ft_strtrim(redirs[j], " \n");
				free(redirs[j]);
				redirs[j] = temp;
				cmd->fd_in = eval_heredoc(redirs[j]);
			}
			else
				cmd->fd_in = open(redirs[j], O_RDONLY);
			if (cmd->fd_in < 0)
			{
				write(2, "minishell: ", 11);
				perror(redirs[j]);
				cmd->exit_status = 1;
				if (!cmd->builtin)
					exit(EXIT_FAILURE);
				else if (cmd->builtin)
					return ;
			}
			j++;
		}
		}
		i++;
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
			// if (i == cmd[i]->nr_cmds - 1)
			// 	close(cmd[i]->pipefd[0]);
			// else
			// {
			// 	dup2(cmd[i]->pipefd[1], 1);
			// 	close(cmd[i]->pipefd[1]);
			// 	//close(cmd[i]->pipefd[0]);
			// }
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
	(void)flag;
	// close(cmd[i]->pipefd[0]);
	// close(cmd[i]->pipefd[1]);
	if (cmd[i]->nr_redir_in > 0)
		in_redir(cmd[i]);
	if (cmd[i]->nr_redir_out > 0)
		out_redir(cmd[i]);
}
