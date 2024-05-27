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

int	count_redir_strings(t_redir_token *parse_redir, enum e_redir_types redir_type)
{
	t_redir_token	*temp;
	t_str_node		*text;
	int				i;

	i = 0;
	temp = parse_redir;
	while (temp)
	{
		if (temp->redir_type == redir_type && temp->text_token && temp->text_token->expanded)
		{
			text = temp->text_token->expanded;
			while (text && text->str)
			{
				i++;
				text = text->next;
			}
		}
		temp = temp->next;
	}
	return (i);
}

void	fill_individual_redirs(char ***redir, enum e_redir_types redir_type, t_redir_token *temp, int *i, t_redir_token *parse_redir)
{
	t_str_node	*text;
	int			k;

	*redir = malloc(sizeof(char *) * (count_redir_strings(parse_redir, redir_type) + 1));
	if (!(*redir))
		return ;
	k = 0;
	if (temp->text_token->expanded)
	{
        if (!(*redir)[*i])
            return;
		text = temp->text_token->expanded;
		k = 0;
		while (text && text->str)
		{
			if (redir_type == REDIR_APPEND)
				redir[*i][k++] = ft_strjoin("\n", text->str);
			else
				redir[*i][k++] = ft_strdup(text->str);
			text = text->next;
		}
		redir[*i][k] = NULL;
		(*i)++;
	}
}

void	fill_redirs(t_xcmd *x, t_redir_token *parse_redir)
{
	t_redir_token	*temp;
	int				i;
	int				j;
	int				l;

	i = 0;
	j = 0;
	l = 0;
	
	if (x->nr_redir_in > 0)
		x->infile = malloc(sizeof(char **) * (x->nr_redir_in + 1));
	if (x->nr_redir_out > 0)
		x->out = malloc(sizeof(char **) * (x->nr_redir_out + 1));
	if (x->nr_heredoc > 0)
		x->heredoc = malloc(sizeof(char **) * (x->nr_heredoc + 1));
	temp = parse_redir;
	while (temp)
	{
		if (temp->redir_type == REDIR_INFILE)
			fill_individual_redirs(x->infile, REDIR_INFILE, temp, &i, parse_redir);
		else if (temp->redir_type == REDIR_HEREDOC)
			fill_individual_redirs(x->heredoc, REDIR_HEREDOC, temp, &l, parse_redir);
		else if (temp->redir_type == REDIR_OUTFILE)
			fill_individual_redirs(x->out, REDIR_OUTFILE, temp, &j, parse_redir);
		if (temp->redir_type == REDIR_APPEND)
			fill_individual_redirs(x->out, REDIR_APPEND, temp, &j, parse_redir);
		temp = temp->next;
	}
	if (x->nr_redir_in > 0)
		x->infile[i] = NULL;
	if (x->nr_redir_out > 0)
		x->out[j] = NULL;
	if (x->nr_heredoc > 0)
		x->heredoc[l] = NULL;
	printf("nr_redir_in: %d\n", x->nr_redir_in);
	printf("nr_redir_out: %d\n", x->nr_redir_out);
	printf("nr_heredoc: %d\n", x->nr_heredoc);
}

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
	if (xcmd->nr_redir_in > 0 || xcmd->nr_redir_out > 0 || xcmd->nr_heredoc > 0)
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
	expanded_full = malloc(sizeof(char *) * (i + 1));
	if (!expanded_full)
		return (NULL);
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
