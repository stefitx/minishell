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
	x->outfile = malloc(sizeof(char *) * (x->nr_redir_out + 1));
	x->append = malloc(sizeof(char *) * (x->nr_append + 1));
	while (temp)
	{
		if (temp->redir_type == REDIR_INFILE)
			x->infile[i++] = ft_strdup(temp->text_token->expanded->str);
		else if (temp->redir_type == REDIR_HEREDOC)
			x->infile[i++] = ft_strjoin("\n", temp->text_token->expanded->str);
		else if (temp->redir_type == REDIR_OUTFILE)
			x->outfile[j++] = ft_strdup(temp->text_token->expanded->str);
		else if (temp->redir_type == REDIR_APPEND)
			x->append[j++] = ft_strdup(temp->text_token->expanded->str);
		temp = temp->next;
	}
	x->infile[i] = NULL;
	x->outfile[j] = NULL;
	x->append[j] = NULL;
}

void	fill_cmd(char ***xcmd, t_single_cmd *cmd)
{
	t_text_token	*parse_cmd;
	t_str_node		*parse_cmd2;
	int				i;

	i = 0;
	parse_cmd = cmd->args;
	parse_cmd2 = parse_cmd->expanded;
	while (parse_cmd2)
	{
		parse_cmd2 = parse_cmd2->next;
		i++;
	}
	*xcmd = malloc(sizeof(char *) * (i + 1));
	parse_cmd2 = parse_cmd->expanded;
	i = 0;
	while (parse_cmd2)
	{
		(*xcmd)[i] = ft_strdup(parse_cmd2->str);
		parse_cmd2 = parse_cmd2->next;
		i++;
	}
	(*xcmd)[i] = NULL;
}

void	fill(t_xcmd *xcmd, t_command *cmd, int nr_cmds, pid_t *pid)
{
	t_single_cmd	*cursor;
	t_redir_token	*check_redirs;

	xcmd->nr_cmds = nr_cmds;
	cursor = cmd->cmd_list;
	fill_cmd(&(xcmd->cmd), cursor);
	xcmd->builtin = check_builtin(xcmd->cmd);
	check_redirs = cursor->redirs;
	if (check_redirs != NULL)
		count_redirs(xcmd, check_redirs);
	if (xcmd->nr_redir_in > 0 || xcmd->nr_redir_out > 0
		|| xcmd->nr_append > 0)
		fill_redirs(xcmd, check_redirs);
	pipe_error([i]->pipefd);
	xcmd->pid = pid;
	cursor = cursor->next;
}

t_xcmd	**allocate_and_fill(t_command *cmd, int nr_cmds)
{
	t_xcmd	**xcmd;
	pid_t	*pid;
	int		i;

	xcmd = malloc(sizeof(t_xcmd *) * nr_cmds);
	pid = malloc(sizeof(pid_t) * nr_cmds);
	if (!xcmd)
		return (NULL);
	i = 0;
	while (i < nr_cmds)
	{
		xcmd[i] = malloc(sizeof(t_xcmd));
		if (!xcmd[i])
		{
			while (i > 0)
				free(xcmd[--i]);
			free(xcmd);
			return (NULL);
		}
		(*xcmd)->cmd_id = i;
		fill(xcmd[i], cmd, nr_cmds, pid);
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
