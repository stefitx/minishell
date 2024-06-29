/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 23:19:48 by atudor            #+#    #+#             */
/*   Updated: 2024/06/29 14:38:59 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cmd_not_found(char **cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	check_dir_name(char **cmd, DIR *dir)
{
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
	else if (access(cmd[0], F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
}

void	check_if_directory(char **split_path, char **cmd)
{
	DIR	*dir;

	if (cmd[0] != NULL)
	{
		dir = opendir(cmd[0]);
		if (ft_strchr(cmd[0], '/') != NULL || ft_streq(cmd[0], "~") != 0)
			check_dir_name(cmd, dir);
		else if (split_path == NULL || errno == ENOTDIR)
		{
			if (dir)
				closedir(dir);
			ft_putstr_fd("minishell: ", 2);
			perror(cmd[0]);
			exit(127);
		}
		if (dir)
			closedir(dir);
	}
}
