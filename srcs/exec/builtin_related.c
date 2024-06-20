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

int	builtin_menu(t_xcmd **xcmd, int i, t_data *data)
{
	if (ft_strcmp(xcmd[i]->cmd[0], "exit") == 0)
	{
		if (ft_strcmp(xcmd[i]->cmd[0], "cd") != 0)
			ft_cd(xcmd[i], data->env_list);
		else if (ft_strcmp(xcmd[i]->cmd[0], "echo") != 0)
			ft_echo(xcmd[i]);
		else if (ft_strcmp(xcmd[i]->cmd[0], "env") != 0)
			ft_env(xcmd[i], data);
		else if (ft_strcmp(xcmd[i]->cmd[0], "export") != 0)
			ft_export(xcmd[i], data);
		else if (ft_strcmp(xcmd[i]->cmd[0], "pwd") != 0)
			ft_pwd(xcmd[i]);
		else if (ft_strcmp(xcmd[i]->cmd[0], "unset") != 0)
			ft_unset(xcmd[i], data);
		return (1);
	}
	else
		return (0);
}

void	builtin_execution(t_data *data, t_xcmd **xcmd, int i)
{
	int		orig_stdin;
	int		orig_stdout;
	int		flag;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	flag = 0;
	if (xcmd[i]->nr_heredoc > 0)
		dup2(eval_heredoc(xcmd[i]->redirs, xcmd[i]), STDIN_FILENO);
	redirections(xcmd, i, &flag);
	if (!builtin_menu(xcmd, i, data) && ft_strcmp(xcmd[i]->cmd[0], "exit") != 0)
	{
		dup2(orig_stdin, STDIN_FILENO);
		dup2(orig_stdout, STDOUT_FILENO);
		close(orig_stdin);
		close(orig_stdout);
		ft_exit(xcmd[i], &flag);
	}
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
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
