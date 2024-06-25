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

void	final_wait(t_xcmd **cmd, t_data *data)
{
	int	nr_cmds;
	int	i;

	nr_cmds = (*cmd)->nr_cmds;
	i = 0;
	while (i < (*cmd)->nr_cmds)
	{
		if (nr_cmds == 1 && cmd[i]->builtin)
			break ;
		save_exitstatus(cmd, i);
		i++;
	}
	env_set_var(&data->env_list, "?",
		ft_itoa_err(cmd[nr_cmds - 1]->exit_status));
}

void	child(t_xcmd **cmd, int i, t_data *data, t_sigacts *sigacts)
{
	int	j;
	int	heredoc_fd;
	int	flag;

	heredoc_fd = 0;
	if (cmd[i]->nr_heredoc > 0)
	{
		update_sig_handlers(sigacts, SIG_HANDLE_HDOC);
		heredoc_fd = eval_heredoc(cmd[i]->redirs, cmd[i], sigacts);
		if (heredoc_fd != -1)
			dup2(heredoc_fd, STDIN_FILENO);
	}
	update_sig_handlers(sigacts, SIG_HANDLE_NONE);
	redirections(cmd, i, &flag);
	if (cmd[i]->builtin)
		builtin_menu(cmd, i, data);
	j = 3;
	while (j < FOPEN_MAX)
		close(j++);
	if (!cmd[i]->builtin)
		execution(data, cmd[i]);
	exit(cmd[i]->exit_status);
}

void	exec_daddy(t_xcmd **cmd, t_data *data, int i, t_sigacts *sigacts)
{
	update_sig_handlers(sigacts, SIG_HANDLE_EXEC);
	while (i < (*cmd)->nr_cmds)
	{
		if ((cmd[i]->builtin && (*cmd)->nr_cmds == 1)
			|| ft_streq(cmd[i]->cmd[0], "exit") != 0)
			builtin_exec(data, cmd, i, sigacts);
		else
		{
			if (i < (*cmd)->nr_cmds - 1)
				pipe_error(cmd[i]->pipefd);
			update_sig_handlers(sigacts, SIG_HANDLE_BLCK);
			(*cmd)->pid[i] = fork();
			if ((*cmd)->pid[i] == 0)
				child(cmd, i, data, sigacts);
		}
		if (i > 0 && (*cmd)->nr_cmds > 1)
		{
			close(cmd[i - 1]->pipefd[0]);
			close(cmd[i - 1]->pipefd[1]);
		}
		if (cmd[i]->nr_heredoc > 0 && cmd[i]->cmd
			&& (*cmd)->pid[i] != 0)
			save_exitstatus(cmd, i);
		i++;
	}
}

void	redir_and_execute(t_xcmd **cmd, t_data *data, t_sigacts *s)
{
	int		orig_stdin;
	int		orig_stdout;
	int		i;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	i = 0;
	exec_daddy(cmd, data, i, s);
	update_sig_handlers(s, SIG_HANDLE_BLCK);
	final_wait(cmd, data);
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
}

void	parse_and_exec(char *s, t_data *data, t_sigacts *sigacts)
{
	t_xcmd		**xcmd;
	t_command	*cmd;

	update_sig_handlers(sigacts, SIG_HANDLE_NONE);
	cmd = parse_command(s, data->env_list);
	if (!cmd || !cmd->cmd_list)
	{
		update_sig_handlers(sigacts, SIG_HANDLE_IDLE);
		return ;
	}
	add_history(s);
	xcmd = init_exe_cmd(cmd);
	redir_and_execute(xcmd, data, sigacts);
	free_xcmd(xcmd, (*xcmd)->nr_cmds);
	clear_command(cmd);
	update_sig_handlers(sigacts, SIG_HANDLE_IDLE);
}

/*
simple heredoc doesnt catch signals
*/