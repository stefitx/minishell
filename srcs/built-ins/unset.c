/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:03:21 by atudor            #+#    #+#             */
/*   Updated: 2024/04/17 17:03:24 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../exec/exec.h"

void	ft_unset(t_xcmd *xcmd, t_data *data)
{
	int		i;

	if (xcmd->exit_status != 0)
		return ;
	i = 1;
	while (xcmd->cmd[i])
	{
		env_unset_var(&data->env_list, xcmd->cmd[i]);
		i++;
	}
	xcmd->exit_status = 0;
}
