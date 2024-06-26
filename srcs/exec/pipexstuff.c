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
	if (env == NULL)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], s, ft_strlen(s)) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	to_split = ft_substr_err(env[i], ft_strlen(s), ft_strlen(env[i]));
	split_path = ft_split_err(to_split, ':');
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
		temp = ft_strjoin_err(split_path[i], "/");
		path = ft_strjoin_err(temp, command);
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
	check_if_directory(split_path, cmd);
	if (access(cmd[0], F_OK) == 0)
	{
		if (access(cmd[0], X_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(cmd[0]);
			exit(EXIT_FAILURE);
		}
		return (free_arr(split_path), cmd[0]);
	}
	path = construct_command_path(split_path, cmd[0]);
	if (path != NULL)
		return (free_arr(split_path), path);
	cmd_not_found(cmd);
	exit(127);
}

void	execution(t_data *data, t_xcmd *cmd)
{
	char	**env;

	if (cmd->cmd[0] == NULL || !cmd->cmd || !cmd->cmd[0][0])
		exit(0);
	env = env_to_arr(data->env_list);
	cmd->path = access_path(cmd->cmd, env);
	if (execve(cmd->path, cmd->cmd, env) == -1)
	{
		cmd_not_found(cmd->cmd);
		free(cmd->path);
		free_arr(env);
		exit(127);
	}
}
