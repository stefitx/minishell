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
		waitpid((*cmd)->pid[i], &status, 0);
		if (WIFEXITED(status))
			(*cmd)[i].exit_status = WEXITSTATUS(status);
		i++;
	}
}

void	redir_and_execute(t_env *env_list, t_xcmd **cmd)
{
	int				i;
	char			**env;

	i = 0;
	env = env_to_arr(env_list);
	while (i < (*cmd)->nr_cmds)
	{
		(*cmd)->pid[i] = fork();
		if ((*cmd)->pid[i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			redirections(cmd, i);
			//if (cmd[i]->builtin)
				//builtin_execution(env, cmd[i]);
			execution(env, cmd[i]);
			exit(0);
		}
		else
			if (i < (*cmd)->nr_cmds)
				close(cmd[i]->pipefd[1]);
		i++;
	}
	save_exitstatus(cmd, i);
}

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
