/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:13:56 by atudor            #+#    #+#             */
/*   Updated: 2024/04/19 18:41:50 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/signals.h"

static void	rl_blank_line(void)
{
	int		i;
	char	*temp;

	temp = ft_strdup_err(rl_line_buffer);
	i = 0;
	while (i++ < 2)
		ft_strappend(&temp, " ");
	rl_on_new_line();
	rl_replace_line(temp, 1);
	rl_redisplay();
	free(temp);
}

void	sig_handler_idle(int signal)
{
	if (signal == SIGINT || signal == SIGQUIT)
	{
		g_signals = signal;
		rl_blank_line();
		if (signal == SIGINT)
		{
			printf("ihshivhheifhhehhf\n");
			write(STDOUT_FILENO, "\n", 1);
			rl_replace_line("", 1);
			rl_on_new_line();
			rl_redisplay();
		}
		else if (ft_strlen(rl_line_buffer) <= 2)
			rl_replace_line("", 1);
	}
}
