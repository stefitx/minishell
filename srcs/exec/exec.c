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
			// printf("exit status: %d\n", cmd[i]->exit_status);
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

- heredocs get evluated first, before any syntax error or any commands
$? < $? | <$? <$?





shortking👑$ echo "Hello, World" > $gyufi
AddressSanitizer:DEADLYSIGNAL
=================================================================
==17398==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x000100733c58 bp 0x00016f6d69a0 sp 0x00016f6d66f0 T0)
==17398==The signal is caused by a READ memory access.
==17398==Hint: address points to the zero page.
    #0 0x100733c58 in fill_redirs+0x690 (minishell:arm64+0x10000bc58)
    #1 0x100734344 in fill+0x31c (minishell:arm64+0x10000c344)
    #2 0x1007351e8 in allocate_and_fill+0x544 (minishell:arm64+0x10000d1e8)
    #3 0x1007352fc in init_exe_cmd+0x48 (minishell:arm64+0x10000d2fc)
    #4 0x1007334c0 in parse_and_exec+0xe8 (minishell:arm64+0x10000b4c0)
    #5 0x10072d738 in main+0x374 (minishell:arm64+0x100005738)
    #6 0x18eaf50dc  (<unknown module>)

==17398==Register values:
 x[0] = 0x0000000103404f10   x[1] = 0x0000000000000010   x[2] = 0x0000000000000000   x[3] = 0x0000000103404f20  
 x[4] = 0x0000000103404f20   x[5] = 0x0000000000000001   x[6] = 0x000000016eedc000   x[7] = 0x0000000000000001  
 x[8] = 0x0000000000000000   x[9] = 0x0000000000000000  x[10] = 0x0000000103404f18  x[11] = 0x000000700001ffff  
x[12] = 0x000000016f6d5f00  x[13] = 0xb282da96c51b7fad  x[14] = 0x0000000000007e01  x[15] = 0x0000000000000006  
x[16] = 0x00000001010a8ad8  x[17] = 0x00000001010e80b8  x[18] = 0x0000000000000000  x[19] = 0x000000016f6d6d80  
x[20] = 0x000000010072d3c4  x[21] = 0x000000016f6d6ea0  x[22] = 0x0000000100b5d910  x[23] = 0x000000016f6d6f20  
x[24] = 0x000000016f6d6f60  x[25] = 0x000000018eb745bb  x[26] = 0x0000000000000000  x[27] = 0x0000000000000000  
x[28] = 0x0000000000000000     fp = 0x000000016f6d69a0     lr = 0x0000000100733744     sp = 0x000000016f6d66f0  
AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV (minishell:arm64+0x10000bc58) in fill_redirs+0x690
==17398==ABORTING


*/