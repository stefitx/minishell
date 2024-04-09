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

#include "../inc/minishell.h"

char	**find_path()
{
	char	*to_split;
	char	**split_path;

	to_split = ft_substr(getenv("PATH="), 5, ft_strlen(getenv("PATH")));
	split_path = ft_split(to_split, ':');
	free(to_split);
	return (split_path);
}

char	**find_command(char *argv)
{
	char	**command;

	command = ft_split(argv, ' ');
	return (command);
}

char	*construct_command_path(char **split_path, char *command)
{
	char	*path;
	int		i;
	char	*temp;

	i = 0;
	while (split_path[i])
	{
		temp = ft_strjoin(split_path[i], "/");
		path = ft_strjoin(temp, command);
		free(temp);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*access_path(char *argv)
{
	char	*path;
	char	**split_path;
	char	**command;

	split_path = find_path();
	command = find_command(argv);
	if (access(command[0], F_OK) == 0)
	{
		if (access(command[0], X_OK) == -1)
		{
			ft_putstr_fd(command[0], 2);
			ft_putstr_fd(": Permission denied", 2);
			exit(126);
		}
		return (command[0]);
	}
	path = construct_command_path(split_path, command[0]);
	if (path != NULL)
		return (path);
	ft_putstr_fd("zsh: ", 2);
	ft_putstr_fd(command[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
	return (NULL);
}

void	execute_command(char **env, char *command)
{
	char	**cmd;
	char	*path;
	int		i;

	cmd = find_command(command);
	i = 0;
	while (cmd[i] != NULL)
		i++;
	path = access_path(command);
	if (execve(path, cmd, env) == -1)
	{
		free_matrix(cmd, i);
		free(path);
		perror("Command execution failed");
		exit(EXIT_FAILURE);
	}
}

void	exec_cmd(char **env, char *command)
{
	pid_t	pid;
	pid = fork();
	if (pid == 0)
	{
		execute_command(env, command);
		exit(0);
	}
	int status;
	waitpid(pid, &status, 0);
}

void	parse_and_exec(char *s)
{
	t_xcmd			**xcmd;
	// t_xdata			xdata;
	t_command		*cmd;
	t_token			*raw_tokens;
	t_ref_token		*tokens;


	raw_tokens = split_tokens(s);
	tokens = refine_tokens(raw_tokens);
	cmd = build_commands(tokens);
	token_list_clear(raw_tokens);
	ref_token_list_clear(tokens);
	xcmd = init_exe_cmd(cmd);
	(void)xcmd;
	//do infile
	// execute command
	// do outfile redirs
	// xdata.cmd_arr = &xcmd;
}
