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

void	save_exitstatus(t_xcmd **cmd, t_data *data, int i)
{
	//int	status;
	int last_cmd;

	(void)i;
	last_cmd = (*cmd)->nr_cmds - 1;
	env_set_var(&data->env_list, "?", ft_itoa((*cmd)[last_cmd].exit_status));
}

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
	redirections(xcmd, i, &flag);
	if (!builtin_menu(xcmd, i, data) && ft_strcmp(xcmd[i]->cmd[0], "exit") != 0)
	{
		dup2(orig_stdin, STDIN_FILENO);
		dup2(orig_stdout, STDOUT_FILENO);
		ft_exit(xcmd[i], &flag);
	}
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
}

void	redir_and_execute(t_xcmd **cmd, t_data *data)
{
	int		i;
	int		status;

	i = 0;
	while (i < (*cmd)->nr_cmds)
	{
		if (!cmd[i]->builtin)
			(*cmd)->pid[i] = fork();
		if ((*cmd)->pid[i] == 0 && !cmd[i]->builtin)
		{
			signal(SIGINT, SIG_DFL);
			redirections(cmd, i, &status);
			execution(data, cmd[i]);
			exit(0);
		}
		if (cmd[i]->builtin)
			builtin_execution(data, cmd, i);
		if (i < (*cmd)->nr_cmds)
			close(cmd[i]->pipefd[1]);
		if (!cmd[i]->builtin)
		{
			waitpid((*cmd)->pid[i], &status, 0);
			cmd[i]->exit_status = WEXITSTATUS(status);
			printf("exit status: %d\n", cmd[i]->exit_status);
		}
		i++;
	}
	save_exitstatus(cmd, data, i);
}

void	parse_and_exec(char *s, t_data *data)
{
	t_xcmd		**xcmd;
	t_command	*cmd;

	cmd = parse_command(s, data->env_list);
	if (!cmd || !cmd->cmd_list)
		return ;
	add_history(s);
	xcmd = init_exe_cmd(cmd);
	redir_and_execute(xcmd, data);
	clear_single_cmd_list(cmd->cmd_list);
	free(cmd);
}

/*
- free everything!
- lexer??
- ambiguous redirects????
*/