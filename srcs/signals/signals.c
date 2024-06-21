#include "../../inc/minishell.h"
#include "../../inc/signals.h"

static void    sig_handler_init(struct sigaction *sigact)
{
	sigemptyset(&(*sigact).sa_mask);
	(*sigact).sa_flags = 0;
	sigaction(SIGINT, sigact, NULL);
	sigaction(SIGQUIT, sigact, NULL);
}

void    update_sig_handler(struct sigaction *sigact, enum e_sig_handle mode)
{
	if (mode == SIG_HANDLE_IDLE)
		(*sigact).sa_handler = sig_handler_idle;
	else if (mode == SIG_HANDLE_EXEC)
		(*sigact).sa_handler = SIG_DFL;
	else
		(*sigact).sa_handler = SIG_IGN;
    sig_handler_init(sigact);
}
