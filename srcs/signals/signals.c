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

void	sig_handler_init(t_sigaction *sigact, int signal)
{
	sigemptyset(&(*sigact).sa_mask);
	sigaddset(&(*sigact).sa_mask, signal);
	sigact->sa_flags = 0;
	sigaction(signal, sigact, NULL);
}

void	update_sig_handlers(t_sigacts *sigacts, enum e_sig_handle mode)
{
	if (mode == SIG_HANDLE_IDLE)
		sigacts->sigint_sigact.sa_handler = sig_handler_idle;
	else if (mode == SIG_HANDLE_HDOC)
		sigacts->sigint_sigact.sa_handler = SIG_DFL;
	else if (mode == SIG_HANDLE_EXEC)
		sigacts->sigint_sigact.sa_handler = sig_handler_exec;
	else if (mode == SIG_HANDLE_BLCK)
		sigacts->sigint_sigact.sa_handler = SIG_IGN;
	else
		sigacts->sigint_sigact.sa_handler = SIG_DFL;
	if (mode == SIG_HANDLE_HDOC)
		sigacts->sigquit_sigact.sa_handler = SIG_IGN;
	else
		sigacts->sigquit_sigact.sa_handler = sigacts->sigint_sigact.sa_handler;
	sig_handler_init(&sigacts->sigint_sigact, SIGINT);
	sig_handler_init(&sigacts->sigquit_sigact, SIGQUIT);
}

	//char *modes[] = { "None", "Idle", "Heredoc", "Exec", "Block" };
	//printf("Mode %s set on PID %ld\n", modes[mode], (long)getpid());