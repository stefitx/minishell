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

void	close_and_exit(int *heredoc_fd, pid_t pid)
{
	close(heredoc_fd[0]);
	close(heredoc_fd[1]);
	if (pid == 0)
		exit(130);
}

int	eval_heredoc(t_redir_token *redir_list, t_xcmd *cmd, pid_t pid)
{
	int					heredoc_fd[2];
	t_redir_token		*heredoc;
	struct sigaction	sigact;

	heredoc = redir_list;
	heredoc_fd[0] = -3;
	if (!heredoc || !heredoc->text_token)
		return (-1);
	while (heredoc && heredoc->text_token && cmd->exit_status != 130)
	{
		if (pid == 0)
			update_sig_handler(&sigact, SIG_HANDLE_NONE);
		if (heredoc->redir_type == REDIR_HEREDOC)
			heredoc_print(heredoc->text_token->expanded_full, heredoc_fd, cmd);
		if (g_signals == SIGINT)
		{
			close_and_exit(heredoc_fd, pid);
			return (-1);
		}
		heredoc = heredoc->next;
	}
	close(heredoc_fd[1]);
	if (pid == 0)
		exit(0);
	return (heredoc_fd[0]);
}
