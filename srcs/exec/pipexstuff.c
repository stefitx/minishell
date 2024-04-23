/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexstuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 23:19:48 by atudor            #+#    #+#             */
/*   Updated: 2024/04/09 23:19:53 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**find_path(char **env, char *s)
{
	int		i;
	char	*to_split;
	char	**split_path;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], s, ft_strlen(s)) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	to_split = ft_substr(env[i], ft_strlen(s), ft_strlen(env[i]));
	split_path = ft_split(to_split, ':');
	free(to_split);
	return (split_path);
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

char	*access_path(char **cmd, char **env)
{
	char	*path;
	char	**split_path;

	split_path = find_path(env, "PATH=");
	if (access(cmd[0], F_OK) == 0)
	{
		if (access(cmd[0], X_OK) == -1)
		{
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			exit(126);
		}
		return (cmd[0]);
	}
	path = construct_command_path(split_path, cmd[0]);
	if (path != NULL)
		return (path);
	ft_putstr_fd("zsh: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
	return (NULL);
}

void	execution(t_data *data, t_xcmd *cmd)
{
	char	**env;
	int		i;

	env = env_to_arr(data->env_list);
	cmd->path = access_path(cmd->cmd, env);
	if (execve(cmd->path, cmd->cmd, env) == -1)
	{
		free(cmd->path);
		i = 0;
		while (env[i])
			free(env[i++]);
		free(env);
		perror("Command execution failed");
		exit(EXIT_FAILURE);
	}
}
