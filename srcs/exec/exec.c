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

// t_cmd	**init_cmd_array(/*struct that holds all commands, or idk?*/ int	nr_cmds)
// {
// 	int	i;
// 	t_cmd	*cmds;

// 	cmds = malloc(sizeof(t_cmd) * nr_cmds);
// 	if (!cmds)
// 		return (NULL);
// 	i = 0;
// 	while (i < nr_cmds)
// 	{
// 		cmds[i].cmd_id = i;
// 		cmds[i].nr_of_cmd = nr_cmds;
// 		cmds[i].cmd = cmd;
// 		cmds[i].path = get_path(cmd);
// 		cmds[i].filename_out = filename_out;
// 		cmds[i].filename_in = filename_in;
// 		if (pipe(cmds[i].pipefd) == -1)
// 		{
// 			write(2, "Error creating pipe", 19);
// 			exit(EXIT_FAILURE);
// 		}
// 		cmds[i].pid = fork();
// 		if (cmds[i].pid == 0)
// 			exec_cmd(cmd, i);
// 		i++;
// 	}
// 	return (&cmds);
// }

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

// void	redirections(t_cmd *cmd, int i) //actually just some redirections for now
// {
// 	int	fd_in;
// 	int	fd_out;

// 	if (cmd[i].filename_in != NULL)
// 	{
// 		fd_in = open(cmd[i].filename_in, O_RDONLY);
// 		if (fd_in < 0)
// 		{
// 			perror(cmd[i].filename_in);
// 			exit(EXIT_FAILURE);
// 		}
// 		dup2(fd_in, 0); //read end
// 		close(fd_in);
// 	} //this will take from infile but it won't write to the pipe (if there's no pipe after, it prints to stdout)
// 	if (cmd[i].filename_out != NULL)
// 	{
// 		fd_out = open(cmd[i].filename_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd_out < 0)
// 		{
// 			perror(cmd[i].filename_out);
// 			exit(EXIT_FAILURE);
// 		}
// 		dup2(fd_out, 1); //write end
// 		close(fd_out);
// 	} // this will print to the outfile, but depending on whether it's the first command or not, i have to write the code for the read end
// 	//need to write the code depending on where the pipe char is in the command, to know if we're writing to a pipe or reading from it
// 	//if there is no pipe, command can still be redirected so this is what that is lol
// 	//execute_command();
// 	exit(EXIT_FAILURE);
// }