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

t_export	*get_existing_node_position(t_data *data, char *name)
{
	t_export	*cursor;
	
	if (!data || !data->export_list || !name)
		return (NULL);
	cursor = data->export_list;
	while (cursor->next)
	{
		if (cursor->next->name && !ft_strncmp(cursor->next->name, name, ft_strlen(name)))
			return (cursor);
		cursor = cursor->next;
	}
	return (NULL);
}

void	add_node(t_data *data, t_export *new, char c)
{
	t_export	*cursor;
	t_export	*cursor2;
	t_export	*temp;
	char		*temp2;
	
	if (!data || !data->export_list || !new)
		return ;
	cursor2 = get_existing_node_position(data, new->name);
	if (!cursor2)
	{
		if (data->export_list->next)
		{
			cursor = data->export_list->next;
			while (cursor->next)
				cursor = cursor->next;
			cursor->next = new;
		}
		else
			data->export_list->next = new;
	}
	else if (new->value)
	{
		if (c == '+' && cursor2->next->value)
		{
			temp2 = ft_strjoin(cursor2->next->value, new->value);
			new->value = temp2;
		}
		temp = cursor2->next;
		cursor2->next = new;
		cursor2->next->next = temp->next;
	}
	env_set_var(&data->env_list, new->name, new->value);
}

t_export	*create_new_node(char *str, char *full_str)
{
	t_export	*new;
	int equal_pos = has_equal_sign(str);
	
	new = (t_export *)malloc(sizeof(t_export));
	if (!new)
		return (NULL);

	else
	if (equal_pos == 0)
	{
		new->name = ft_strdup(str);
		new->value = NULL;
	}
	else if (equal_pos >= 0)
	{
		if (!is_addition(str))
			new->name = ft_substr(str, 0, equal_pos);
		else
			new->name = ft_substr(str, 0, equal_pos - 1);
		new->value = ft_strdup(full_str + equal_pos + 1);
	}
	new->str = ft_strdup(full_str);
	new->next = NULL;
	return (new);
}

int	no_arg_export(t_xcmd *xcmd, t_data *data)
{
	t_env	*cursor;
	t_export	*cursor2;

	if (xcmd->expanded_full[1] == NULL)
	{
		if (data->env_list)
		{
			cursor = data->env_list;
			while (cursor->name[0] != '?')
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(cursor->name, 1);
				ft_putstr_fd("=", 1);
				ft_putstr_fd(cursor->val, 1);
				ft_putstr_fd("\n", 1);
				cursor = cursor->next;
			}
		}
		cursor2 = data->export_list->next;
		while (cursor2)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(cursor2->name, 1);
			if (cursor2->value)
			{
				ft_putstr_fd("=", 1);
				ft_putstr_fd("\"", 1);
				ft_putstr_fd(cursor2->value, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
			cursor2 = cursor2->next;
		}
		return (1);
	}
	return (0);
}


void print_invalid_identifier(char* cmd, int* exit_status)
{
    ft_putstr_fd("export: `", 2);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd("`: not a valid identifier\n", 2);
    *exit_status = 1;
}

char determine_node_type(t_data* data, char* expanded_full)
{
    if (!already_exists(data, expanded_full)
        || (already_exists(data, expanded_full)
        && !is_addition(expanded_full)))
        return 'x';
    else if (is_addition(expanded_full)
        && already_exists(data, expanded_full))
        return '+';
    return 'x';
}

void	ft_export(t_xcmd *xcmd, t_data *data)
{
	int			i;
	int			j;
	t_export	*new;
	char		c;

	if (no_arg_export(xcmd, data))
		return ;

	for (i = 1, j = 1; xcmd->cmd[i]; i++)
	{
		if (is_invalid(xcmd->expanded_full[1]))
		{
			print_invalid_identifier(xcmd->cmd[i], &xcmd->exit_status);
			continue;
		}
		while (!is_invalid(xcmd->expanded_full[j]))
		{
			new = create_new_node(xcmd->cmd[i], xcmd->expanded_full[j]);
			c = determine_node_type(data, xcmd->expanded_full[j]);
			add_node(data, new, c);
			j++;
		}
	}
}


// void	ft_export(t_xcmd *xcmd, t_data *data)
// {
// 	int			i;
// 	int			j;
// 	t_export	*new;
// 	char		c;

// 	if (no_arg_export(xcmd, data))
// 		return ;
// 	i = 1;
// 	j = 1;
// 	while (xcmd->cmd[i])
// 	{
// 		while (!is_invalid(xcmd->expanded_full[j]))
// 		{
// 			if (xcmd->expanded_full[j] == NULL)
// 				return ;
// 			new = create_new_node(xcmd->cmd[i], xcmd->expanded_full[j]);
// 			if (!already_exists(data, xcmd->expanded_full[j])
// 				|| (already_exists(data, xcmd->expanded_full[j])
// 				&& !is_addition(xcmd->expanded_full[j])))
// 				c = 'x';
// 			else if (is_addition(xcmd->expanded_full[j])
// 				&& already_exists(data, xcmd->expanded_full[j]))
// 				c = '+';
// 			add_node(data, new, c);
// 			j++;
// 		}
// 		if (is_invalid(xcmd->expanded_full[1]))
// 		{
// 			ft_putstr_fd("export: `", 2);
// 			ft_putstr_fd(xcmd->cmd[i], 2);
// 			ft_putstr_fd("`: not a valid identifier\n", 2);
// 			xcmd->exit_status = 1;
// 		}
// 		i++;
// 	}
// }

//update env
