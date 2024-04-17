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

void	ft_cd(t_xcmd *cmd, char **env)
{
    if (cmd->cmd[1] != NULL)
    {
        if (chdir(cmd->cmd[1]) != 0) 
        {
            ft_putstr_fd("minishell: cd: ", 2);
            perror(cmd->cmd[1]);
            cmd->exit_status = 1;
            return ;
        }
    }
    else
    {
        char **home_path = NULL;
		home_path= find_path(env, "HOME=");
        if (home_path == NULL || *home_path == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			cmd->exit_status = 1;
			return;
		}
		else
			chdir(home_path[0]);
    }
}
