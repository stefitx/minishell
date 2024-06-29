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
	while (g_signals != SIGINT)
	{
		line = readline("> ");
		if (!line || ft_streq(line, limiter) || g_signals == SIGINT)
		{
			free(line);
			if (g_signals == SIGINT)
				cmd->exit_status = 130;
			break ;
		}
		write(heredoc_fd[1], line, ft_strlen(line));
		write(heredoc_fd[1], "\n", 1);
		free(line);
	}
}

int	eval_heredoc(t_redir_token *redir_list, t_xcmd *cmd, t_sigacts *s)
{
	int				heredoc_fd[2];
	t_redir_token	*heredoc;

	heredoc = redir_list;
	heredoc_fd[0] = -3;
	if (!heredoc || !heredoc->text_token)
		return (-1);
	while (heredoc && heredoc->text_token && cmd->exit_status != 130)
	{
		(void)s;
		update_sig_handlers(s, SIG_HANDLE_HDOC);
		if (heredoc->redir_type == REDIR_HEREDOC)
			heredoc_print(heredoc->text_token->expanded_full, heredoc_fd, cmd);
		heredoc = heredoc->next;
	}
	close(heredoc_fd[1]);
	return (heredoc_fd[0]);
}

int	get_heredoc_fd(t_redir_token *redir_list)
{
	int				heredoc_fd[2];
	t_redir_token	*heredoc;

	heredoc = redir_list;
	heredoc_fd[0] = -3;
	if (!heredoc || !heredoc->text_token)
		return (-1);
	while (heredoc && heredoc->text_token)
		heredoc = heredoc->next;
	return (heredoc_fd[0]);
}

void	heredoc_offspring(t_xcmd *xcmd, t_sigacts *sigacts)
{
	int		orig_stdin;
	int		orig_stdout;
	int		heredoc_fd;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	if (g_signals)
		xcmd->exit_status = 130;
	else
	{
		update_sig_handlers(sigacts, SIG_HANDLE_HDOC);
		heredoc_fd = eval_heredoc(xcmd->redirs, xcmd, sigacts);
		close(heredoc_fd);
		dup2(orig_stdin, STDIN_FILENO);
		dup2(orig_stdout, STDOUT_FILENO);
		close(orig_stdin);
		close(orig_stdout);
	}
	exit(xcmd->exit_status);
}

void	heredoc_bastard_birth(t_xcmd *xcmd, t_sigacts *sigacts)
{
	pid_t	pid;
	int		status;

	if (xcmd->nr_heredoc > 0)
	{
		xcmd->heredoc_fd = 42;
		pid = fork();
		if (pid == 0)
			heredoc_offspring(xcmd, sigacts);
		else
		{
			waitpid(pid, &status, 0);
			if (WIFSIGNALED(status))
			{
				g_signals = SIGINT;
				xcmd->exit_status = 130;
			}
		}
	}
}
