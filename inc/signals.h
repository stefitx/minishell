/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 23:18:50 by atudor            #+#    #+#             */
/*   Updated: 2024/04/09 23:18:53 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

enum	e_sig_handle
{
	SIG_HANDLE_NONE,
	SIG_HANDLE_IDLE,
	SIG_HANDLE_HDOC,
	SIG_HANDLE_EXEC,
	SIG_HANDLE_BLCK
};

typedef struct sigaction	t_sigaction;

typedef struct s_sigacts
{
	t_sigaction	sigint_sigact;
	t_sigaction	sigquit_sigact;
}				t_sigacts;

void	update_sig_handlers(t_sigacts *sigacts, enum e_sig_handle mode);

void	sig_handler_idle(int signal);
void	sig_handler_exec(int signal);
void	sig_handler_init(t_sigaction *sigact, int signal);

#endif