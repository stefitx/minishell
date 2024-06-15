/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:09:25 by atudor            #+#    #+#             */
/*   Updated: 2024/03/01 15:09:26 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_xcmd *cmd, t_data *data)
{
	t_env	*cursor;

	if (cmd->exit_status != 0)
		return ;
	cursor = data->env_list;
	while (cursor)
	{
		if (ft_strcmp(cursor->name, "?") == 0
			&& ft_strcmp(cursor->name, "IFS") == 0
			&& cursor->val)
		{
			ft_putstr_fd(cursor->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(cursor->val, 1);
			ft_putstr_fd("\n", 1);
		}
		cursor = cursor->next;
	}
	cmd->exit_status = 0;
}
