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

t_cmd	**init_cmd_array(/*struct that holds all commands, or idk?*/ int	nr_cmds)
{
	int	i;
	t_cmd	*cmds;

	cmds = malloc(sizeof(t_cmd) * nr_cmds);
	if (!cmds)
		return (NULL);
	i = 0;
	while (i < nr_cmds)
	{
		cmds[i].cmd_id = i;
		cmds[i].nr_of_cmd = nr_cmds;
		cmds[i].cmd = cmd;
		cmds[i].path = get_path(cmd);
		cmds[i].filename_out = filename_out;
		cmds[i].filename_in = filename_in;
		if (pipe(cmds[i].pipefd) == -1)
		{
			write(2, "Error creating pipe", 19);
			exit(EXIT_FAILURE);
		}
		cmds[i].pid = fork();
		if (cmds[i].pid == 0)
			exec_cmd(cmd, i);
		i++;
	}
	return (&cmds);
}

void	exec_cmd(t_cmd *cmd, int i) //actually just some redirections for now
{
	int	fd_in;
	int	fd_out;

	if (cmd[i].filename_in != NULL)
	{
		fd_in = open(cmd[i].filename_in, O_RDONLY);
		if (fd_in < 0)
		{
			perror(cmd[i].filename_in);
			exit(EXIT_FAILURE);
		}
		dup2(fd_in, 0); //read end
		close(fd_in);
	} //this will take from infile but it won't write to the pipe (if there's no pipe after, it prints to stdout)
	if (cmd[i].filename_out != NULL)
	{
		fd_out = open(cmd[i].filename_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			perror(cmd[i].filename_out);
			exit(EXIT_FAILURE);
		}
		dup2(fd_out, 1); //write end
		close(fd_out);
	} // this will print to the outfile, but depending on whether it's the first command or not, i have to write the code for the read end
	//need to write the code depending on where the pipe char is in the command, to know if we're writing to a pipe or reading from it
	//if there is no pipe, command can still be redirected so this is what that is lol
	//execute_command();
	exit(EXIT_FAILURE);
}