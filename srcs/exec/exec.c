/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:13:56 by atudor            #+#    #+#             */
/*   Updated: 2024/03/04 15:13:58 by atudor           ###   ########.fr       */
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

void	builtin_execution(char **env, t_xcmd **cmd, int i)
{
	t_xcmd	*xcmd;
	int orig_stdin = dup(STDIN_FILENO);
	int orig_stdout = dup(STDOUT_FILENO);

	redirections(cmd, i);
	xcmd = cmd[i];
	if (strcmp(xcmd->cmd[0], "cd") == 0)
	{
		//see whats wrong with strcmp
		ft_cd(xcmd, env);
	}
	else if (strcmp(xcmd->cmd[0], "echo") == 0)
		ft_echo(xcmd);
	// else if (ft_strcmp(cmd->cmd[0], "env") == 0)
	// 	ft_env(env);
	// else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
	// 	ft_pwd();
	// else if (ft_strcmp(cmd->cmd[0], "export") == 0)
	// 	ft_export(cmd->cmd, env);
	// else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
	// 	ft_unset(cmd->cmd, env);

	// else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
	// 	ft_exit(cmd->cmd);
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
}

void	redir_and_execute(t_env *env_list, t_xcmd **cmd)
{
	int				i;
	char			**env;

	i = 0;
	env = env_to_arr(env_list);
	while (i < (*cmd)->nr_cmds)
	{
		if (!cmd[i]->builtin)
			(*cmd)->pid[i] = fork();
		if ((*cmd)->pid[i] == 0 && !cmd[i]->builtin)
		{
			signal(SIGINT, SIG_DFL);
			redirections(cmd, i);
			execution(env, cmd[i]);
			exit(0);
		}
		else
		{
			if (cmd[i]->builtin)
			{
				builtin_execution(env, cmd, i);
				save_exitstatus(cmd, i);
			}
			if (i < (*cmd)->nr_cmds)
				close(cmd[i]->pipefd[1]);
		}
		i++;
	}
	save_exitstatus(cmd, i);
}

//i need to do smth that re-redirects the fds after use, and i think it's better to so it in the functions themselves

void	parse_and_exec(char *s, t_env *env)
{
	t_xcmd			**xcmd;
	t_command		*cmd;
	t_token			*raw_tokens;
	t_ref_token		*tokens;

	raw_tokens = split_tokens(s);
	tokens = refine_tokens(raw_tokens);
	cmd = build_commands(tokens);
	token_list_clear(raw_tokens);
	ref_token_list_clear(tokens);
	xcmd = init_exe_cmd(cmd);
	redir_and_execute(env, xcmd);
	clear_single_cmd_list(cmd->cmd_list);
	free(cmd);
}
