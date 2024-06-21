/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:13:56 by atudor            #+#    #+#             */
/*   Updated: 2024/04/19 17:24:09 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	heredoc_print(char *limiter, int *heredoc_fd, t_xcmd *cmd)
{
	char	*line;

	if (heredoc_fd[0] != -3)
	{
		close(heredoc_fd[0]);
		close(heredoc_fd[1]);
	}
	pipe_error(heredoc_fd);
	while (1)
	{
		line = readline("> ");
		printf("exit_status: %d\n", cmd->exit_status);
		if (!line || ft_streq(line, limiter))
		{
			free(line);
			break ;
		}
		if (cmd->exit_status == 130)
		{
			exit(130);
		}
		write(heredoc_fd[1], line, ft_strlen(line));
		write(heredoc_fd[1], "\n", 1);
		free(line);
	}
}

void	sig_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "HERE\n", 6);
		printf("Heredoc signal hander called!\nMy PID: %ld\nParent PID: %ld\n\n", (long)getpid(), (long)getppid());
		g_signals = signal;
	}
}

void	sig_heredoc(struct sigaction *sigact, t_xcmd *cmd)
{
	(void)cmd;
	(*sigact).sa_handler = sig_handler_heredoc;
	if (g_signals == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		cmd->exit_status = 130;
	}
}

int	eval_heredoc(t_redir_token *redir_list, t_xcmd *cmd)
{
	int				heredoc_fd[2];
	t_redir_token	*heredoc;
	//struct sigaction	sigact;

	heredoc = redir_list;
	heredoc_fd[0] = -3;
	if (!heredoc || !heredoc->text_token)
		return (-1);
	while (heredoc && heredoc->text_token && cmd->exit_status != 130)
	{
		//sig_heredoc(&sigact, cmd);
		printf("exit_status: %d\n", cmd->exit_status);
		if (heredoc->redir_type == REDIR_HEREDOC)
			heredoc_print(heredoc->text_token->expanded_full, heredoc_fd, cmd);
		heredoc = heredoc->next;
	}
	if (g_signals == SIGINT)
	{
		printf("returning -1\n");
		close(heredoc_fd[0]);
		exit(130);
	}
	close(heredoc_fd[1]);
	return (heredoc_fd[0]);
}
