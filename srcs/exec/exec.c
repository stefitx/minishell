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

void	save_exitstatus(t_xcmd **cmd, int i)
{
	int	status;

	i = 0;
	while (i < (*cmd)->nr_cmds)
	{
		if (!(*cmd)->builtin)
		{
			waitpid((*cmd)->pid[i], &status, 0);
			if (WIFEXITED(status))
				(*cmd)[i].exit_status = WEXITSTATUS(status);
		}
		i++;
	}
}

void	builtin_execution(t_data *data, t_xcmd **cmd, int i)
{
	int		orig_stdin;
	int		orig_stdout;
	char	**env;
	t_xcmd	*xcmd;
	int		flag;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	env = env_to_arr(data->env_list);
	xcmd = cmd[i];
	flag = 0;
	redirections(cmd, i, &flag);
	if (ft_strcmp(xcmd->cmd[0], "cd") != 0)
		ft_cd(xcmd, env);
	else if (ft_strcmp(xcmd->cmd[0], "echo") != 0)
		ft_echo(xcmd);
	else if (ft_strcmp(xcmd->cmd[0], "env") != 0)
		ft_env(xcmd, data);
	else if (ft_strcmp(xcmd->cmd[0], "exit") != 0)
	{
		dup2(orig_stdin, STDIN_FILENO);
		dup2(orig_stdout, STDOUT_FILENO);
		ft_exit(xcmd, &flag);
	}
	else if (ft_strcmp(xcmd->cmd[0], "export") != 0)
	{
		ft_export(xcmd, data);
	}
		// else if (strcmp(xcmd->cmd[0], "pwd") == 0)
		// 	ft_pwd();
		// else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		// 	ft_unset(cmd->cmd, env);
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
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
		{
			//printf("builtin\n");
			builtin_execution(data, cmd, i);
		}
		if (i < (*cmd)->nr_cmds)
			close(cmd[i]->pipefd[1]);
		if (!cmd[i]->builtin)
			waitpid((*cmd)->pid[i], &status, 0);
		i++;
	}
	save_exitstatus(cmd, i);
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
	// int i = 0;
	// while (xcmd[0]->expanded_full[i])
	// {
	// 	printf("cmd[%d]: %s\n", i, xcmd[0]->expanded_full[i]);
	// 	i++;
	// }
	redir_and_execute(xcmd, data);
	clear_single_cmd_list(cmd->cmd_list);
	free(cmd);
}

/*
- deal with the freaking pointers darling
- WORKING HISTORY ASAP PLS BABE (Done :D dunno if these were meant for me lmao)
- free everything babyyyyy
- lexer??
- put the exit status in the env
- sabe exit statuses CORRECTLY
- what in the world is up with ft_strcmp? (Returns 0 (false) if they're equal,
	returns a non-zero value otherwise (counter-intuitive, I know))
- ambiguous redirects????
*/


// ok so we have 3 cases: a=b, a=, a
// free export arr in the end
// shortking👑$ export b
// is not addition
// new->name: 
// new->value: ""
// new->str: b
// found in export list
// [1]    61259 segmentation fault  ./minishell