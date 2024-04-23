/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:09:07 by atudor            #+#    #+#             */
/*   Updated: 2024/04/18 12:42:44 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
# include "../exec/exec.h"

// int	already_exits(t_data *data, char *name)
// {
// 	int		i;
// 	char	*temp;

// 	if (!ft_strchr(name, '='))
// 		temp = ft_strdup(name);
// 	else
// 		temp = ft_substr(name, 0, ft_strlen(name) - ft_strlen(ft_strchr(name, '=')));
// 	printf("temp: %s\n", temp);
// 	i = 0;
// 	while (data->export_arr[i].name)
// 	{
// 		if (ft_strcmp(data->export_arr[i].name, temp) != 0)
// 		{
// 			free(temp);
// 			printf("found in export_arr\n");
// 			return (1);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (data->env_list)
// 	{
// 		if (ft_strcmp(data->env_list->name, temp) != 0)
// 		{
// 			free(temp);
// 			printf("found in env_list\n");
// 			return (1);
// 		}
// 		data->env_list = data->env_list->next;
// 	}
// 	free(temp);
// 	return (0);
// }

// int	is_addition(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '+' && str[i + 1] == '=')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// static int	is_invalid(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (!str)
// 		return (1);
// 	if (!ft_isalpha(str[i]) && str[i] != '_')
// 		return (1);
// 	while (str[i] && str[i] != '=')
// 	{
// 		if (!ft_isalnum(str[i]) && str[i] != '_' && (str[i] != '+' && str[i + 1] != '='))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

void	init_export(t_export **export_arr)
{
	*export_arr = (t_export *)malloc(sizeof(t_export) * 1);
	(*export_arr)[0].name = NULL;
	(*export_arr)[0].value = NULL;
	(*export_arr)[0].str = NULL;
}

// int	init_export(t_export **export_arr, char **cmd, char **env)
// {
// 	int	nr_cmd;
// 	int	env_len;
// 	int	i;

// 	nr_cmd = 1;
// 	while (cmd[nr_cmd])
// 		nr_cmd++;
// 	env_len = 0;
// 	while (env[env_len])
// 		env_len++;
// 	// *export_arr = (t_export *)malloc(sizeof(t_export) * (nr_cmd + env_len));
// 	i = 0;
// 	while (i < (nr_cmd + env_len - 1))
// 	{
// 		if (i < env_len)
// 		{
// 			(*export_arr)[i].name = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
// 			(*export_arr)[i].value = ft_strchr(env[i], '=') + 1;;
// 			(*export_arr)[i].str = ft_strjoin("declare -x ", env[i]);
// 		}
// 		else
// 		{
// 			(*export_arr)[i].name = NULL;
// 			(*export_arr)[i].value = NULL;
// 			(*export_arr)[i].str = NULL;
// 		}
// 		i++;
// 	}
// 	return (i);
// }

// void	update_var(t_env **env_list, char *str, t_export **export_arr, char c)
// {
// 	char	*name;
// 	char	*temp;
// 	char	*val;
// 	int		i;
	
	
// 	name = ft_substr(str, 0, ft_strchr(str, '=') - str);
// 	val = ft_strchr(str, '=') + 1;
// 	i = 0;
// 	while ((*export_arr)[i].name)
// 	{
// 		if (ft_strcmp((*export_arr)[i].name, name) != 0)
// 		{
// 			temp = (*export_arr)[i].value;
// 			free((*export_arr)[i].value);
// 			free((*export_arr)[i].str);
// 			if (c == '=')
// 			{
// 				printf("replacing value\n");
// 				(*export_arr)[i].value = val;
// 				(*export_arr)[i].str = ft_strjoin("declare -x ", str);
// 			}
// 			else if (c == '+')
// 			{
// 				printf("adding value\n");
// 				(*export_arr)[i].str = ft_strjoin("declare -x ", ft_strjoin(temp, val));
// 				(*export_arr)[i].value = ft_strjoin(temp, val);
// 			}
// 			free(temp);
// 			free(name);
// 			free(val);
// 			return ;
// 		}
// 		i++;
// 	}
// 	if (c == '=')
// 		env_set_var(env_list, name, val);
// 	else if (c == '+')
// 		env_add_var(env_list, name, ft_strjoin((*export_arr)[i].value, val));
// 	free(name);
// 	free(val);
// }

// void	add_to_export_arr(t_data *data, char *name, char *val, char *str)
// {
// 	int		i;
// 	t_export	*temp;

// 	i = 0;
// 	while (data->export_arr[i].name)
// 		i++;
// 	temp = (t_export *)malloc(sizeof(t_export) * (i + 2));
// 	i = 0;
// 	while (data->export_arr[i].name)
// 	{
// 		temp[i].name = data->export_arr[i].name;
// 		temp[i].value = data->export_arr[i].value;
// 		temp[i].str = data->export_arr[i].str;
// 		i++;
// 	}
// 	temp[i].name = name;
// 	temp[i].value = val;
// 	temp[i].str = str;
// 	temp[i + 1].name = NULL;
// 	temp[i + 1].value = NULL;
// 	temp[i + 1].str = NULL;
// 	free(data->export_arr);
// 	data->export_arr = temp;
// }

// void	add_to_env_list(t_data *data, char *name, char *val)
// {
// 	t_env	*new;
// 	t_env	*cursor;
	
// 	new = ft_calloc(1, sizeof(t_env));
// 	if (!new)
// 		return ;
// 	new->name = name;
// 	new->val = val;
// 	new->next = NULL;
// 	// cursor = data->env_list;
// 	// while (cursor->next)
// 	// 	cursor = cursor->next;
// 	// cursor->next = new;
// 	if (data->env_list == NULL) {
//     data->env_list = new;
// 	} else {
//     cursor = data->env_list;
//     while (cursor->next)
//         cursor = cursor->next;
//     cursor->next = new;
// }
// }

void	ft_export(t_xcmd *xcmd, t_data *data)
{
	int		i;
	// char	*name;
	// char	*val;
	t_env	*cursor;

		//printf("here\n");
	if (xcmd->cmd[1] == NULL)
	{
		if (data->env_list)
		{
			cursor = data->env_list;
			while (cursor->next)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(cursor->name, 1);
				ft_putstr_fd("=", 1);
				ft_putstr_fd(cursor->val, 1);
				ft_putstr_fd("\n", 1);
				cursor = cursor->next;
			}
		}
		i = 0;
		while (data->export_arr[i].name)
		{
			//make sure to print 
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(data->export_arr[i].str, 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
		return ;
	}
	// i = 1;
	// while (xcmd->cmd[i])
	// {
		// if (!is_invalid(xcmd->cmd[i]))
		// {
		// 	if (!ft_strchr(xcmd->cmd[i], '='))
		// 	{
		// 		name = ft_strdup(xcmd->cmd[i]);
		// 		val = NULL;
		// 	}
		// 	else
		// 	{
		// 		name = ft_substr(xcmd->cmd[i], 0, ft_strlen(xcmd->cmd[i]) - ft_strlen(ft_strchr(xcmd->cmd[i], '=')));
		// 		val = ft_strdup(ft_strchr(xcmd->cmd[i], '=') + 1);
		// 	}
		// 	printf("this is valid: %s\n", xcmd->cmd[i]);
		// 	if (!already_exits(data, xcmd->cmd[i]) )
		// 	{
		// 		printf("does not exist\n");
		// 		add_to_export_arr(data, name, val, xcmd->cmd[i]);
		// 		if (val != NULL)
		// 		{
		// 			//env_add_var(&data->env_list, name, val);
		// 		}
		// 		printf("added %s\n", name);
		// 		// env = env_to_arr(*env_list);
		// 	}
			// else if (already_exits(export_arr, xcmd->cmd[i]) && !is_addition(xcmd->cmd[i]))
			// {
			// 	printf("does exist, not addition\n");
			// 	update_var(env_list, xcmd->cmd[i], &export_arr, '=');
			// }
			// else if (is_addition(xcmd->cmd[i]) && already_exits(export_arr, xcmd->cmd[i]))
			// {
			// 	printf("does exist, addition\n");
			// 	update_var(env_list, xcmd->cmd[i], &export_arr, '+');
			// }
	// 	}
	// 	else
	// 	{
	// 		ft_putstr_fd("export: `", 2);
	// 		ft_putstr_fd(xcmd->cmd[i], 2);
	// 		ft_putstr_fd("': not a valid identifier\n", 2);
	// 		xcmd->exit_status = 1;
	// 	}
	// 	i++;
	// }

}

//update env
