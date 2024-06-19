/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 23:18:50 by atudor            #+#    #+#             */
/*   Updated: 2024/04/09 23:18:53 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ambiguous_redir(t_text_token *redir, t_xcmd *cmd)
{
	int				i;
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
		if (!cmd->builtin && cmd->cmd != NULL && cmd->cmd[0] != NULL)
			exit(1);
		return (1);
	}
	return (0);
}

void	pipe_error(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		write(2, "Error creating pipe", 19);
		exit(EXIT_FAILURE);
	}
}

void	save_exitstatus(t_xcmd **cmd, int i)
{
	int	status;

	waitpid((*cmd)->pid[i], &status, 0);
	if (WIFEXITED(status))
		cmd[i]->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			cmd[i]->exit_status = 130;
			printf("\n");
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			cmd[i]->exit_status = 131;
			printf("Quit: %d\n", WTERMSIG(status));
		}
	}
}
