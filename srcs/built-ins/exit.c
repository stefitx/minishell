/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:09:33 by atudor            #+#    #+#             */
/*   Updated: 2024/06/29 15:45:12 by atudor           ###   ########.fr       */
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

void	it_is_number(t_xcmd *xcmd, int *flag)
{
	int	i;

	i = ft_atoi(xcmd->cmd[1]);
	if (xcmd->cmd[2])
	{
		if (!*flag)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		xcmd->exit_status = 1;
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		xcmd->exit_status = (unsigned int)i;
		if (*flag)
			return ;
		exit((unsigned int)i);
	}
}

void	numeric_argument_required(t_xcmd *xcmd, int *flag)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(xcmd->cmd[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	xcmd->exit_status = 2;
	if (*flag)
		return ;
	exit(2);
}

void	ft_exit(t_xcmd *xcmd, t_data *data, int *flag)
{
	if (xcmd->exit_status != 0)
		return ;
	if (!xcmd->cmd || !xcmd->cmd[0])
		return ;
	if (xcmd->cmd[1])
	{
		if (ft_isnumber(xcmd->cmd[1]))
			it_is_number(xcmd, flag);
		else
			numeric_argument_required(xcmd, flag);
	}
	else
	{
		if (*flag)
			return ;
		write(STDOUT_FILENO, "exit\n", 5);
		exit(ft_atoi(env_get_var(data->env_list, "?")->val));
	}
}
