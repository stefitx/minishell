/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:09:07 by atudor            #+#    #+#             */
/*   Updated: 2024/03/01 15:09:08 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	already_exits(t_export *export_arr, char *name)
{
	int	i;

	i = 0;
	while (export_arr[i].name)
	{
		if (ft_strcmp(export_arr[i].name, name) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_addition(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

static int	ft_isvalid(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	init_export(t_export **export_arr, char **cmd, char **env)
{
	int	nr_cmd;
	int	env_len;
	int	i;

	nr_cmd = 1;
	while (cmd[nr_cmd])
		nr_cmd++;
	env_len = 0;
	while (env[env_len])
		env_len++;
	*export_arr = (t_export *)malloc(sizeof(t_export) * (nr_cmd + env_len - 1));
	i = 0;
	while (i < (nr_cmd + env_len - 1))
	{
		if (i < env_len)
		{
			(*export_arr)[i].name = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
			(*export_arr)[i].value = ft_strchr(env[i], '=') + 1;;
			(*export_arr)[i].str = ft_strjoin("declare -x ", env[i]);
		}
		else
		{
			(*export_arr)[i].name = NULL;
			(*export_arr)[i].value = NULL;
			(*export_arr)[i].str = NULL;
		}
		i++;
	}
	return (i);
}

static void	ft_export(t_xcmd *xcmd, t_env *env_list, char **env)
{
	int		i;
	int		j;
	t_export	*export_arr;

	i = 1;
	while (xcmd->cmd[i])
	{
		if (ft_isvalid(xcmd->cmd[i]))
		{
			j = init_export(&export_arr);
			if (!is_addition(xcmd->cmd[i]))
			{
				export_arr[j].name = ft_substr(xcmd->cmd[i], 0, ft_strchr(xcmd->cmd[i], '=') - xcmd->cmd[i]);
				export_arr[j].value = ft_strchr(xcmd->cmd[i], '=') + 1;
				export_arr[j].str = ft_strjoin("declare -x ", xcmd->cmd[i]);
				env_add_var(&env_list, export_arr[j].name, export_arr[j].value);
				// if (ft_strcmp(name, "PATH") == 0)
				// 	update_path(env, val);
				// else
				// 	update_env(env, name, val);
				// free(name);
			}

		// 	name = ft_substr(xcmd->cmd[i], 0, ft_strchr(xcmd->cmd[i], '=') - xcmd->cmd[i]);
		// 	val = ft_strchr(xcmd->cmd[i], '=') + 1;
		// 	if (ft_strcmp(name, "PATH") == 0)
		// 		update_path(env, val);
		// 	else
		// 		update_env(env, name, val);
		// 	free(name);
		// }
		else
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(xcmd->cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		i++;
	}
}
