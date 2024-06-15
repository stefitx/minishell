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
		while (*s != '\0')
		{
			if (*s != 'n')
				return (0);
			s++;
		}
		return (1);
	}
	return (0);
}

int	*parse_args(t_xcmd *cmd)
{
	int	*i_n_flag;
	int	n_flag;

	n_flag = 0;
	i_n_flag = ft_malloc(sizeof(int) * 2);
	i_n_flag[1] = 0;
	i_n_flag[0] = 1;
	while (cmd->cmd[i_n_flag[0]])
	{
		if (ft_strncmp(cmd->cmd[i_n_flag[0]], "-n", 2) == 0)
		{
			n_flag = check_n_flag(cmd->cmd[i_n_flag[0]]);
			if (n_flag == 1)
			{
				i_n_flag[1] = 1;
				i_n_flag[0]++;
			}
			else
				break ;
		}
		else
			break ;
	}
	return (i_n_flag);
}

void	ft_echo(t_xcmd *cmd)
{
	int	*i_n_flag;

	if (cmd->exit_status != 0)
		return ;
	i_n_flag = parse_args(cmd);
	while (cmd->cmd[i_n_flag[0]])
	{
		ft_putstr_fd(cmd->cmd[i_n_flag[0]], 1);
		if (cmd->cmd[i_n_flag[0] + 1])
			ft_putstr_fd(" ", 1);
		i_n_flag[0]++;
	}
	if (!i_n_flag[1])
		ft_putstr_fd("\n", 1);
	cmd->exit_status = 0;
	free(i_n_flag);
}
