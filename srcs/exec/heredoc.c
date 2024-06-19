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

void	heredoc_print(char *limiter, int *heredoc_fd)
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
		if (!line || ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		write(heredoc_fd[1], line, ft_strlen(line));
		write(heredoc_fd[1], "\n", 1);
		free(line);
	}
}

int	eval_heredoc(t_redir_token *redir_list)
{
	int				heredoc_fd[2];
	t_redir_token	*heredoc;

	heredoc = redir_list;
	heredoc_fd[0] = -3;
	if (!heredoc || !heredoc->text_token)
		return (-1);
	while (heredoc && heredoc->text_token)
	{
		if (heredoc->redir_type == REDIR_HEREDOC)
			heredoc_print(heredoc->text_token->expanded_full, heredoc_fd);
		heredoc = heredoc->next;
	}
	close(heredoc_fd[1]);
	return (heredoc_fd[0]);
}
