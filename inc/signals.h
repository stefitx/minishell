#ifndef SIGNALS_H
#define SIGNALS_H

#include <signal.h>

enum	e_sig_handle
{
	SIG_HANDLE_NONE,
	SIG_HANDLE_IDLE,
	SIG_HANDLE_EXEC
};

void    update_sig_handler(struct sigaction *sigact, enum e_sig_handle mode);

void	sig_handler_idle(int signal);

#endif