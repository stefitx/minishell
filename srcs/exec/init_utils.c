/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:16:23 by atudor            #+#    #+#             */
/*   Updated: 2024/04/09 15:16:26 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_cmds(t_command *cmd)
{
	int				nr_cmds;
	t_single_cmd	*cursor;

	nr_cmds = 0;
	cursor = cmd->cmd_list;
	while (cursor)
	{
		nr_cmds++;
		cursor = cursor->next;
	}
	return (nr_cmds);
}

void	count_args(t_text_token *text, char ***args)
{
	int	i;

	i = 0;
	while (text)
	{
		if (text->expanded)
			i++;
		text = text->next;
	}
	(*args) = ft_malloc(sizeof(char *) * (i + 1));
}

void	count_redirs(t_xcmd *xcmd, t_redir_token *parse_redir)
{
	t_redir_token	*temp;

	xcmd->nr_redir_in = 0;
	xcmd->nr_redir_out = 0;
	xcmd->nr_heredoc = 0;
	temp = parse_redir;
	while (temp)
	{
		if (temp->redir_type == REDIR_INFILE)
			xcmd->nr_redir_in++;
		else if (temp->redir_type == REDIR_OUTFILE
			|| temp->redir_type == REDIR_APPEND)
			xcmd->nr_redir_out++;
		else if (temp->redir_type == REDIR_HEREDOC)
			xcmd->nr_heredoc++;
		temp = temp->next;
	}
	// printf("nr_redir_in: %d\n", xcmd->nr_redir_in);
	// printf("nr_redir_out: %d\n", xcmd->nr_redir_out);
	// printf("nr_heredoc: %d\n", xcmd->nr_heredoc);
}

int	check_builtin(char **xcmd)
{
	if (xcmd[0] == NULL || xcmd == NULL)
		return (0);
	if (ft_strcmp(xcmd[0], "cd") != 0)
		return (1);
	if (ft_strcmp(xcmd[0], "echo") != 0)
		return (1);
	if (ft_strcmp(xcmd[0], "env") != 0)
		return (1);
	if (ft_strcmp(xcmd[0], "exit") != 0)
		return (1);
	if (ft_strcmp(xcmd[0], "export") != 0)
		return (1);
	if (ft_strcmp(xcmd[0], "pwd") != 0)
		return (1);
	if (ft_strcmp(xcmd[0], "unset") != 0)
			return (1);
	else
		return (0);
}
