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

void	changedir(char	**cmd)
{
	if (!ft_strcmp(cmd[0]))
		return (2);
	else
	{
		if (chdir(cmd[1]) == -1)
		{
			perror("cd: ");
			perror(cmd[1]);
			perror(": No such file or directory");
		}
	}
}

/*not finished at all*/