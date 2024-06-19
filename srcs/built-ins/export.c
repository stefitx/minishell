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
#include "../exec/exec.h"

void	add_node(t_data *data, t_export *new)
{
	t_env	*cursor;
	char	*temp;

	if (!data || !data->env_list || !new)
		return ;
	cursor = env_get_var(data->env_list, new->name);
	if (cursor && new->add == 1)
	{
		temp = ft_strjoin_err(cursor->val, new->value);
		free(new->value);
		new->value = temp;
	}
	env_set_var(&data->env_list, new->name, new->value);
	free(new);
}

t_export	*create_new_node(char *str, char *full_str)
{
	t_export	*new;
	int			equal_pos;

	equal_pos = has_equal_sign(str);
	new = (t_export *)ft_malloc(sizeof(t_export));
	new->add = 0;
	if (full_str[equal_pos + 1] == '\0' || equal_pos == 0)
	{
		new->name = ft_strdup_err(ft_strtrim_err(full_str, "=+"));
		if (equal_pos == 0)
			new->value = NULL;
		else
			new->value = ft_strdup("\0");
	}
	else if (equal_pos > 0)
		equal_sign(equal_pos, full_str, str, new);
	return (new);
}

int	no_arg_export(t_xcmd *xcmd, t_data *data)
{
	t_env	*cursor;

	if (xcmd->expanded_full[1] == NULL && data->env_list)
	{
		cursor = data->env_list;
		while (cursor)
		{
			if (cursor->name && cursor->name[0] != '?'
				&& ft_strcmp(cursor->name, "IFS") == 0)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(cursor->name, 1);
				if (cursor->val)
				{
					ft_putstr_fd("=\"", 1);
					ft_putstr_fd(cursor->val, 1);
					ft_putstr_fd("\"", 1);
				}
				ft_putstr_fd("\n", 1);
			}
			cursor = cursor->next;
		}
		return (1);
	}
	return (0);
}

void	print_invalid_identifier(char *cmd, int *exit_status)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("`: not a valid identifier\n", 2);
	*exit_status = 1;
}

void	ft_export(t_xcmd *xcmd, t_data *data)
{
	int			i;
	int			j;
	t_export	*new;

	if (xcmd->exit_status != 0)
		return ;
	if (no_arg_export(xcmd, data))
		return ;
	i = 1;
	j = 1;
	while (xcmd->cmd[i] && xcmd->expanded_full[j])
	{
		if (is_invalid(xcmd->expanded_full[j]))
			print_invalid_identifier(xcmd->cmd[i], &xcmd->exit_status);
		if (xcmd->expanded_full[j] && !is_invalid(xcmd->expanded_full[j]))
		{
			new = create_new_node(xcmd->cmd[i], xcmd->expanded_full[j]);
			add_node(data, new);
		}
		i++;
		j++;
	}
}
