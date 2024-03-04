/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:13:56 by atudor            #+#    #+#             */
/*   Updated: 2024/03/04 15:13:58 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_cmds(/*struct that holds all commands,*/ int	nr_cmds)
{
	int	i;
	t_cmd	*cmds;

	cmds = malloc(sizeof(t_cmd) * nr_cmds);
	if (!cmds)
		return (NULL);
	i = 0;
	while (i < nr_cmds)
	{
		cmds[i].cmd_id = i;
		cmds[i].nr_of_cmd = nr_cmds;
		cmds[i].cmd = cmd;
		cmds[i].path = get_path(cmd);
		cmds[i].filename_out = filename_out;
		
	}
}