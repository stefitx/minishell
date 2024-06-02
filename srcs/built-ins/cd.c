/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:08:48 by atudor            #+#    #+#             */
/*   Updated: 2024/03/01 15:08:49 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_arr(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void		change_directories(t_xcmd *cmd, char **env, t_env *env_list)
{
	char	*oldpwd;
	char	**home_path;

	home_path= find_path(env, "HOME=");
	if (home_path == NULL || *home_path == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		cmd->exit_status = 1;
		free_arr(env);
		free_arr(home_path);
		return ;
	}
	else
	{
		oldpwd = find_path(env, "PWD=")[0];
		env_set_var(&env_list, "OLDPWD", oldpwd);
		free(oldpwd);
		chdir(home_path[0]);
		env_set_var(&env_list, "PWD", home_path[0]);
		cmd->exit_status = 0;
		free_arr(home_path);
	}
	free_arr(env);
}

void	ft_cd(t_xcmd *cmd, t_env *env_list)
{
	char	*oldpwd;
	char 	*newpwd;
	char	**env;
	int		res;

	env = env_to_arr(env_list);
	if (cmd->exit_status != 0)
		return ;
	if (cmd->cmd[1] != NULL)
	{
		oldpwd = getcwd(NULL, 0);
		res = chdir(cmd->cmd[1]);
		if (res == 0) 
		{
			env_set_var(&env_list, "OLDPWD", oldpwd);
			newpwd = getcwd(NULL, 0);
			env_set_var(&env_list, "PWD", newpwd);
			cmd->exit_status = 0;
		}
		else
		{
			ft_putstr_fd("minishell: cd: ", 2);
			perror(cmd->cmd[1]);
			cmd->exit_status = 1;
			return ;
		}
		free_arr(env);
	}
	else
		change_directories(cmd, env, env_list);
}
