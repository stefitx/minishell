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

void	eval_heredoc(char *limiter)
{
	// int		fd;
	// char	*line;

	// heredoc = ft_strtrim(heredoc, " \n");
	// fd = 0;
	// while (1)
	// {
	// 	line = readline("> ");
	// 	if (!line || ft_strcmp(line, heredoc))
	// 	{
	// 		free(line);
	// 		break ;
	// 	}
	// 	write(fd, line, ft_strlen(line));
	// 	write(fd, "\n", 1);
	// 	free(line);
	// }
	// close(fd);
}

void	in_redir(t_xcmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->infile[i])
	{
		// if (cmd->infile[i][0] == '\n')
		// 	eval_heredoc(cmd->infile[i]);
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

void	redirections(t_xcmd *cmd)
{
	int i;

	if (cmd->nr_redir_in > 0)
		in_redir(cmd);
}
