/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:08:36 by atudor            #+#    #+#             */
/*   Updated: 2024/03/01 15:08:41 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_n_flag(char *s)
{
	if (ft_strncmp(s, "-n", 2) == 0)
	{
		s++;
		while (*s)
		{
			if (*s != 'n')
				return (0);
			s++;
		}
		return (1);
	}
	return (0);
}

void	ft_echo(t_xcmd *cmd)
{
	int	i;
	int	n_flag;
	int	count;

	i = 1;
	n_flag = 0;
	count = 0;
	if (cmd->exit_status != 0)
		return ;
	if (cmd->cmd[1] && ft_strncmp(cmd->cmd[i], "-n", 2) == 0)
	{
		n_flag = check_n_flag(cmd->cmd[1]);
		count++;
		i++;
		while (n_flag && cmd->cmd[i] && ft_strncmp(cmd->cmd[i], "-n", 2) == 0)
		{
			n_flag = check_n_flag(cmd->cmd[i]);
			if (n_flag == 0)
				break ;
			if (n_flag == 1)
				count++;
			i++;
		}
	}
	while (cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i], 1);
		if (cmd->cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag && count == 0)
		ft_putstr_fd("\n", 1);
	cmd->exit_status = 0;
}
