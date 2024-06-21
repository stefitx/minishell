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
	SIG_HANDLE_EXEC
};

void	update_sig_handler(struct sigaction *sigact, enum e_sig_handle mode);

void	sig_handler_idle(int signal);
void	sig_handler_exec(int signal);

#endif