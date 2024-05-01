/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:08:57 by atudor            #+#    #+#             */
/*   Updated: 2024/03/01 15:08:58 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
# include "../exec/exec.h"

void	ft_pwd(t_xcmd *xcmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (xcmd->exit_status != 0)
		return ;
	if (!pwd)
	{
		ft_putstr_fd("minishell: pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
		xcmd->exit_status = 1;
	}
	else
	{
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
		xcmd->exit_status = 0;
	}
	free(pwd);
}
