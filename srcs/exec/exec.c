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

int	eval_heredoc(t_redir_token *redir_list)
{
	int		heredoc_fd[2];
	char	*line;
	char	*limiter;
	t_redir_token	*heredoc;

	heredoc = redir_list;
	heredoc_fd[0] = -3;
	while (heredoc && heredoc->text_token)
	{
		if (heredoc->redir_type == REDIR_HEREDOC)
		{
			if (heredoc_fd[0] != -3)
			{
				close(heredoc_fd[0]);
				close(heredoc_fd[1]);
			}
			limiter = heredoc->text_token->expanded->str;
			pipe_error(heredoc_fd);
			while (1)
			{
				line = readline("> ");
				if (!line || ft_strcmp(line, limiter))
				{
					free(line);
					break ;
				}
				write(heredoc_fd[1], line, ft_strlen(line));
				write(heredoc_fd[1], "\n", 1);
				free(line);
			}
		}
		heredoc = heredoc->next;
	}
	close(heredoc_fd[1]);
	return (heredoc_fd[0]);
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
	if (xcmd[i]->nr_heredoc > 0)
		dup2(eval_heredoc(xcmd[i]->redirs), STDIN_FILENO);
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
	int		orig_stdin;
	int		orig_stdout;
	int		heredoc_fd = 0;
	int		nr_cmds;

	int		i;
	int		flag;
	int		status;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	i = 0;
	while (i < (*cmd)->nr_cmds)
	{
		if ((cmd[i]->builtin && (*cmd)->nr_cmds == 1)
		|| ft_strcmp(cmd[i]->cmd[0], "exit") != 0)
			builtin_execution(data, cmd, i);
		else
		{
			if (i < (*cmd)->nr_cmds - 1)
				pipe_error(cmd[i]->pipefd);
			(*cmd)->pid[i] = fork();
			if ((*cmd)->pid[i] == 0)
			{
				signal(SIGINT, SIG_DFL);
				if (cmd[i]->nr_heredoc > 0)
				{
					heredoc_fd = eval_heredoc(cmd[i]->redirs);
					dup2(heredoc_fd, STDIN_FILENO);
				}
				redirections(cmd, i, &flag);
				if (cmd[i]->builtin)
					builtin_menu(cmd, i, data);
				close(cmd[i]->pipefd[1]);
				if (i > 0)
				{
					close(cmd[i - 1]->pipefd[0]);
					close(cmd[i - 1]->pipefd[1]);
				}
				if (i == (*cmd)->nr_cmds - 1)
					close(cmd[i]->pipefd[0]);
				if (!cmd[i]->builtin)
					execution(data, cmd[i]);
				exit(cmd[i]->exit_status);
			}
			
		}
		if (i > 0 && (*cmd)->nr_cmds > 1)
		{
			close(cmd[i - 1]->pipefd[0]); //DONT TOUCH
			close(cmd[i - 1]->pipefd[1]);
			// printf("pipe %d closed\n", cmd[i - 1]->pipefd[0]);
			// printf("pipe %d closed\n", cmd[i - 1]->pipefd[1]);
		}
		// if (i == (*cmd)->nr_cmds - 1)
		// 			close(cmd[i]->pipefd[0]);
		if (cmd[i]->nr_heredoc > 0 && (*cmd)->pid[i] != 0)
			close(heredoc_fd);
			// printf("exit status: %d\n", cmd[i]->exit_status);
		i++;
	}
	i = 0;
	while (i < (*cmd)->nr_cmds)
	{
		// printf("after everythinbg pid: %d, i is %d\n", (*cmd)->pid[i], i);
		status = 0;
		//printf("status: %d\n", status);
		waitpid((*cmd)->pid[i], &status, 0);
		//printf("we get here\n");
		if (WIFEXITED(status))
			cmd[i]->exit_status = WEXITSTATUS(status);
		//printf("exit status: %d\n", cmd[i]->exit_status);
		i++;
	}
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
	//wait3(NULL, 0, NULL);
	nr_cmds = (*cmd)->nr_cmds;
	//printf("nr_cmds: %d\n", nr_cmds);
	//printf("exit status in cmd: %d\n", cmd[nr_cmds-1]->exit_status);
	env_set_var(&data->env_list, "?", ft_itoa(cmd[nr_cmds-1]->exit_status));
	//save_exitstatus(cmd, data, i);
}

void	free_xcmd(t_xcmd **xcmd, int size)
{
	int	i;

	i = 0;
	if (!xcmd || !*xcmd)
		return ;
	while (i < size && xcmd[i])
	{
		if (xcmd[i])
		{
			if (xcmd[i]->cmd)
				free_arr(xcmd[i]->cmd);
			if (xcmd[i]->expanded_full)
				free_arr(xcmd[i]->expanded_full);
			// if (xcmd[i]->pid)
			// 	free(xcmd[i]->pid);
			free(xcmd[i]);
			i++;
		}
	}
	free(xcmd);
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
	clear_single_cmd_list(cmd->cmd_list);
	free(cmd);
	redir_and_execute(xcmd, data);
	free_xcmd(xcmd, (*xcmd)->nr_cmds);
}

/*
when syntax error, history doesn't work
free everything!
FIX MAKEFILE
norminette
*/