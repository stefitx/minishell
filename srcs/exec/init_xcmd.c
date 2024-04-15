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

void	fill_redirs(t_xcmd *x, t_redir_token *parse_redir)
{
	t_redir_token	*temp;
	int				i;
	int				j;

	i = 0;
	j = 0;
	temp = parse_redir;
	x->infile = malloc(sizeof(char *) * (x->nr_redir_in + 1));
	x->out = malloc(sizeof(char *) * (x->nr_redir_out + 1));
	while (temp)
	{
		if (temp->redir_type == REDIR_INFILE)
			x->infile[i++] = ft_strdup(temp->text_token->expanded->str);
		else if (temp->redir_type == REDIR_HEREDOC)
			x->infile[i++] = ft_strjoin("\n", temp->text_token->expanded->str);
		else if (temp->redir_type == REDIR_OUTFILE)
			x->out[j++] = ft_strdup(temp->text_token->expanded->str);
		else if (temp->redir_type == REDIR_APPEND)
			x->out[j++] = ft_strjoin("\n", temp->text_token->expanded->str);
		temp = temp->next;
	}
	x->infile[i] = NULL;
	x->out[j] = NULL;
}

void	fill(t_xcmd *xcmd, t_single_cmd *cursor, int nr_cmds, pid_t *pid)
{
	t_redir_token	*check_redirs;

	xcmd->nr_cmds = nr_cmds;
	xcmd->builtin = check_builtin(xcmd->cmd);
	check_redirs = cursor->redirs;
	if (check_redirs != NULL)
		count_redirs(xcmd, check_redirs);
	if (xcmd->nr_redir_in > 0 || xcmd->nr_redir_out > 0)
		fill_redirs(xcmd, check_redirs);
	xcmd->pid = pid;
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
			i++;
		t_text_token = t_text_token->next;
	}
	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
		return (NULL);
	i = 0;
	t_text_token = cmd->args;
	while (t_text_token)
	{
		if (t_text_token->expanded)
		{
			t_str_node = t_text_token->expanded;
			args[i++] = ft_strdup(t_str_node->str);
		}
		t_text_token = t_text_token->next;
	}
	args[i] = NULL;
	return (args);
}

t_xcmd	**allocate_and_fill(t_command *cmd, int nr_cmds)
{
	t_xcmd			**xcmd;
	t_single_cmd	*t_single_cmd;
	pid_t			*pid;
	int				i;

	xcmd = malloc(sizeof(t_xcmd *) * nr_cmds);
	if (!xcmd)
		return (NULL);
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
		xcmd[i]->cmd = get_cmd_array(t_single_cmd);
		xcmd[i]->cmd_id = i;
		xcmd[i]->nr_cmds = nr_cmds;
		fill(xcmd[i], t_single_cmd, nr_cmds, pid);
		pipe_error(xcmd[i]->pipefd);
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
