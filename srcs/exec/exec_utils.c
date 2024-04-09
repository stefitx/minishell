/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 23:18:50 by atudor            #+#    #+#             */
/*   Updated: 2024/04/09 23:18:53 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pipe_error(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		write(2, "Error creating pipe", 19);
		exit(EXIT_FAILURE);
	}
}
