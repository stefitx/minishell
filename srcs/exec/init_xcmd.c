/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_xcmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 22:40:04 by atudor            #+#    #+#             */
/*   Updated: 2024/04/08 22:40:11 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	fill(t_xcmd *xcmd, t_single_cmd *cursor, int nr_cmds, pid_t *pid)
{
	t_redir_token	*check_redirs;

	xcmd->nr_cmds = nr_cmds;
	xcmd->exit_status = 0;
	xcmd->nr_redir_in = 0;
	xcmd->nr_redir_out = 0;
	xcmd->builtin = check_builtin(xcmd->cmd);
	xcmd->fd_in = -3;
	xcmd->fd_o = -3;
	check_redirs = cursor->redirs;
	if (check_redirs != NULL)
		count_redirs(xcmd, check_redirs);
	xcmd->pid = pid;
	xcmd->redirs = cursor->redirs;
	cursor = cursor->next;
}

char	**get_cmd_array(t_single_cmd *cmd)
{
	t_text_token	*t_text_token;
	t_str_node		*t_str_node;
	char			**args;
	int				i;

	t_text_token = cmd->args;
	i = 0;
	while (t_text_token)
	{
		if (t_text_token->expanded)
		{
			t_str_node = t_text_token->expanded;
			while (t_str_node)
			{
				if (t_str_node->str != NULL)
					i++;
				t_str_node = t_str_node->next;
			}
			i++;
		}
		t_text_token = t_text_token->next;
	}
	args = ft_malloc(sizeof(char *) * (i + 1));
	i = 0;
	t_text_token = cmd->args;
	while (t_text_token)
	{
		if (t_text_token->expanded)
		{
			t_str_node = t_text_token->expanded;
			while (t_str_node)
			{
				
				if (t_str_node->str != NULL)
					args[i++] = ft_strdup(t_str_node->str);
				t_str_node = t_str_node->next;
			}
		}
		t_text_token = t_text_token->next;
	}
	args[i] = NULL;
	return (args);
}

char	**get_expanded_full(t_single_cmd *cmd)
{
	t_text_token	*t_text_token;
	char			**expanded_full;
	int				i;

	t_text_token = cmd->args;
	i = 0;
	while (t_text_token)
	{
		if (t_text_token->expanded_full != NULL)
			i++;
		t_text_token = t_text_token->next;
	}
	expanded_full = ft_malloc(sizeof(char *) * (i + 1));
	t_text_token = cmd->args;
	i = 0;
	while (t_text_token)
	{
		if (t_text_token->expanded_full != NULL)
			expanded_full[i++] = ft_strdup(t_text_token->expanded_full);
		t_text_token = t_text_token->next;
	}
	expanded_full[i] = NULL;
	return (expanded_full);
}

t_xcmd	**allocate_and_fill(t_command *cmd, int nr_cmds)
{
	t_xcmd			**xcmd;
	t_single_cmd	*t_single_cmd;
	pid_t			*pid;
	int				i;

	xcmd = ft_malloc(sizeof(t_xcmd *) * nr_cmds);
	pid = malloc(sizeof(pid_t) * nr_cmds);
	if (!pid)
	{
		free(xcmd);
		return (NULL);
	}
	i = 0;
	t_single_cmd = cmd->cmd_list;
	while (i < nr_cmds && t_single_cmd)
	{
		xcmd[i] = malloc(sizeof(t_xcmd));
		if (!xcmd[i])
		{
			while (i >= 0)
				free(xcmd[i--]);
			free(xcmd);
			return (NULL);
		}
		if (t_single_cmd)
		{
			xcmd[i]->expanded_full = get_expanded_full(t_single_cmd);
			xcmd[i]->cmd = get_cmd_array(t_single_cmd);
		}
		xcmd[i]->cmd_id = i;
		xcmd[i]->nr_cmds = nr_cmds;
		fill(xcmd[i], t_single_cmd, nr_cmds, pid);
		t_single_cmd = t_single_cmd->next;
		i++;
	}
	return (xcmd);
}

t_xcmd	**init_exe_cmd(t_command *cmd)
{
	int	nr_cmds;

	nr_cmds = count_cmds(cmd);
	if (nr_cmds == 0)
		return (NULL);
	return (allocate_and_fill(cmd, nr_cmds));
}
