/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+ +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:49:05 by atudor            #+#    #+#             */
/*   Updated: 2024/04/27 15:44:15 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/signals.h"

static void	sig_handler_init(struct sigaction *sigact)
{
	sigemptyset(&(*sigact).sa_mask);
	(*sigact).sa_flags = 0;
	sigaction(SIGINT, sigact, NULL);
	sigaction(SIGQUIT, sigact, NULL);
}

void	update_sig_handler(struct sigaction *sigact, enum e_sig_handle mode)
{
	if (mode == SIG_HANDLE_IDLE)
		(*sigact).sa_handler = sig_handler_idle;
	else if (mode == SIG_HANDLE_EXEC)
		(*sigact).sa_handler = sig_handler_exec;
	else
		(*sigact).sa_handler = SIG_DFL;
	sig_handler_init(sigact);
	(void)sig_handler_init;
}
