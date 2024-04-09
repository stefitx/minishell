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

#include "../inc/minishell.h"

// t_xcmd	**init_exe_cmd(t_command *cmd)
// {
// 	t_xcmd	**xcmd;
// 	int		nr_cmds;
// 	int		i;
// 	t_single_cmd	*cursor;
// 	t_redir_token	*check_redirs;
// 	pid_t			*pid;

// 	cursor = cmd->cmd_list;
// 	nr_cmds = 0;
// 	while (cursor)
// 	{
// 		nr_cmds++;
// 		cursor = cursor->next;
// 	}
// 	if (nr_cmds == 0)
// 		return (NULL);
// 	xcmd = malloc(sizeof(t_xcmd *) * nr_cmds);
// 	pid = malloc(sizeof(pid_t) * nr_cmds);
// 	if (!xcmd)
// 		return (NULL);
// 	i = 0;
// 	while (i < nr_cmds)
// 	{
// 		xcmd[i] = malloc(sizeof(t_xcmd));
// 		if (!xcmd[i])
// 		{
// 			while (i > 0)
// 				free(xcmd[--i]);
// 			free(xcmd);
// 			return (NULL);
// 		}
// 		xcmd[i]->cmd_id = i;
// 		xcmd[i]->nr_of_cmds = nr_cmds;
// 		cursor = cmd->cmd_list;
// 		fill_cmd(&(xcmd[i]->cmd), cursor);
// 		xcmd[i]->builtin = check_builtin(xcmd[i]->cmd);
// 		xcmd[i]->path = access_path(xcmd[i]->cmd[0]);
// 		check_redirs = cursor->redirs;
// 		if (check_redirs != NULL)
// 			count_redirs(xcmd[i], check_redirs);
// 		if (xcmd[i]->nr_redir_in > 0 || xcmd[i]->nr_redir_out > 0 
// 		|| xcmd[i]->nr_append > 0)
// 			fill_redirs(xcmd[i], check_redirs);
// 		xcmd[i]->pid = pid;
// 		cursor = cursor->next;
// 		i++;
// 	}
// 	return (xcmd);
// }

t_xcmd	**init_exe_cmd(t_command *cmd)
{
    t_xcmd	**xcmd;
    int		nr_cmds;
    int		i;
    t_single_cmd	*cursor;
    pid_t			*pid;

    cursor = cmd->cmd_list;
    nr_cmds = 0;
    while (cursor)
    {
        nr_cmds++;
        cursor = cursor->next;
    }
    if (nr_cmds == 0)
        return (NULL);
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
        fill_xcmd(xcmd[i], cmd, i, nr_cmds, pid);
        i++;
    }
    return (xcmd);
}

void more_init(t_xcmd *xcmd, t_command *cmd, int i, int nr_cmds, pid_t *pid)
{
    t_single_cmd	*cursor;
    t_redir_token	*check_redirs;

    xcmd->cmd_id = i;
    xcmd->nr_of_cmds = nr_cmds;
    cursor = cmd->cmd_list;
    fill_cmd(&(xcmd->cmd), cursor);
    xcmd->builtin = check_builtin(xcmd->cmd);
    xcmd->path = access_path(xcmd->cmd[0]);
    check_redirs = cursor->redirs;
    if (check_redirs != NULL)
        count_redirs(xcmd, check_redirs);
    if (xcmd->nr_redir_in > 0 || xcmd->nr_redir_out > 0 
    || xcmd->nr_append > 0)
        fill_redirs(xcmd, check_redirs);
    xcmd->pid = pid;
    cursor = cursor->next;
}

void	fill_redirs(t_xcmd *xcmd, t_redir_token *parse_redir)
{
	t_redir_token	*temp;
	int				i;
	int				j;

	i = 0;
	j = 0;
	temp = parse_redir;
	xcmd->filename_in = malloc(sizeof(char *) * (xcmd->nr_redir_in + 1));
	xcmd->filename_out = malloc(sizeof(char *) * (xcmd->nr_redir_out + 1));
	xcmd->filename_append = malloc(sizeof(char *) * (xcmd->nr_append + 1));
	while (temp)
	{
		if (temp->redir_type == REDIR_INFILE)
			xcmd->filename_in[i++] = ft_strdup(temp->text_token->expanded->str);
		else if (temp->redir_type == REDIR_OUTFILE)
			xcmd->filename_out[j++] = ft_strdup(temp->text_token->expanded->str);
		else if (temp->redir_type == REDIR_APPEND)
			xcmd->filename_append[j++] = ft_strdup(temp->text_token->expanded->str);
		temp = temp->next;
	}
	xcmd->filename_in[i] = NULL;
	xcmd->filename_out[j] = NULL;
	xcmd->filename_append[j] = NULL;
}

void	count_redirs(t_xcmd *xcmd, t_redir_token *parse_redir)
{
	t_redir_token	*temp;

	xcmd->nr_redir_in = 0;
	xcmd->nr_redir_out = 0;
	xcmd->nr_heredoc = 0;
	xcmd->nr_append = 0;
	temp = parse_redir;
	while (temp)
	{
		if (temp->redir_type == REDIR_INFILE)
			xcmd->nr_redir_in++;
		else if (temp->redir_type == REDIR_OUTFILE)
			xcmd->nr_redir_out++;
		else if (temp->redir_type == REDIR_HEREDOC)
			xcmd->nr_heredoc++;
		else if (temp->redir_type == REDIR_APPEND)
			xcmd->nr_append++;
	}
}

int	check_builtin(char **xcmd)
{
	if (ft_strcmp(xcmd[0], "cd") || ft_strcmp(xcmd[0], "pwd") 
	|| ft_strcmp(xcmd[0], "echo") || ft_strcmp(xcmd[0], "export") 
	|| ft_strcmp(xcmd[0], "unset") || ft_strcmp(xcmd[0], "env"))
			return (1);
	else
		return (0);
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
