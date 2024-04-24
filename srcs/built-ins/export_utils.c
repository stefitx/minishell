/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:09:25 by atudor            #+#    #+#             */
/*   Updated: 2024/03/01 15:09:26 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
# include "../exec/exec.h"

int	already_exists(t_data *data, char *name)
{
	char		*temp;
	t_export	*export_list;
	t_env		*cursor;

	if (!ft_strchr(name, '='))
		temp = ft_strdup(name);
	else if (!ft_strchr(name, '+'))
		temp = ft_substr(name, 0, ft_strlen(name) - ft_strlen(ft_strchr(name, '=')));
	else
		temp = ft_substr(name, 0, ft_strlen(name) - ft_strlen(ft_strchr(name, '+')));
	export_list = data->export_list->next;
	while (export_list)
	{
		if (ft_strcmp(export_list->name, temp) != 0)
		{
			free(temp);
			return (1);
		}
		export_list = export_list->next;
	}
	cursor = data->env_list;
	while (cursor)
	{
		if (ft_strcmp(cursor->name, temp) != 0)
		{
			free(temp);
			return (1);
		}
		cursor = cursor->next;
	}
	free(temp);
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

int	is_invalid(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && (str[i] != '+' && str[i + 1] != '='))
			return (1);
		i++;
	}
	return (0);
}

void	init_export(t_export **export_arr)
{
	t_export	*temp;

	temp = malloc(sizeof(t_export) * 1);
	temp->name = NULL;
	temp->value = NULL;
	temp->str = NULL;
	temp->next = NULL;
	(*export_arr) = temp;
}

int has_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}
