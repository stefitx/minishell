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

void	redir_and_execute(t_env *env_list, t_xcmd **cmd, int **pipes)
{
	int				i;
	char			**env;
	int 			status;

	i = 0;
	env = env_to_arr(env_list);
	while (i < (*cmd)->nr_cmds)
	{
		pipe_error(pipes[i]);
		(*cmd)->pid[i] = fork();
		if ((*cmd)->pid[i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			redirections(&cmd, i, pipes);
			// if (cmd[i]->builtin == 1)
			// 	builtin(cmd[i]);
			// else
			execution(env, cmd[i]);
			//close(pipes[i][1]);
			printf("here\n");
			exit(0);
		}
		//signal(SIGINT, SIG_DFL);
		waitpid((*cmd)->pid[i], &status, 0);
		i++;
	}
}

int		**init_pipes(int nr_cmds)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int *) * (nr_cmds));
	while (i < nr_cmds)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		i++;
	}
	return (pipes);
}

void	parse_and_exec(char *s, t_env *env)
{
	t_xcmd			**xcmd;
	int	**pipes;
	t_command		*cmd;
	t_token			*raw_tokens;
	t_ref_token		*tokens;
	


	raw_tokens = split_tokens(s);
	tokens = refine_tokens(raw_tokens);
	cmd = build_commands(tokens);
	token_list_clear(raw_tokens);
	ref_token_list_clear(tokens);
	xcmd = init_exe_cmd(cmd);
	//printf("nr_cmds: %d\n", xcmd[0]->nr_cmds);
	//xdata.cmd_arr = &xcmd;
	pipes = init_pipes(xcmd[0]->nr_cmds);
	redir_and_execute(env, xcmd, pipes);
	clear_single_cmd_list(cmd->cmd_list);
	free(cmd);
	
}
