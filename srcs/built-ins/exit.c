/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:09:33 by atudor            #+#    #+#             */
/*   Updated: 2024/03/01 15:09:35 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_xcmd *xcmd, int *flag)
{
	int	i;

	i = 0;
	if (xcmd->cmd[1])
	{
		if (ft_isnumber(xcmd->cmd[1]))
		{
			i = ft_atoi(xcmd->cmd[1]);
			if (xcmd->cmd[2])
			{
				ft_putstr_fd("exit\n", 2);
				ft_putstr_fd("minishell: exit: too many arguments\n", 2);
				if (*flag)
					return ;
				xcmd->exit_status = 1;
			}
			else
			{
				ft_putstr_fd("exit\n", 1);
				if (*flag)
					return ;
				//xcmd->exit_status = (unsigned int)i;
				exit((unsigned int)i);
			}
		}
		else
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(xcmd->cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			if (*flag)
				return ;
			xcmd->exit_status = 255;
		}
	}
	else
	{
		if (*flag)
			return ;
		write(STDOUT_FILENO, "exit\n", 5);
		exit(0);
	}
}