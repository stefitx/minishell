#include "../../inc/minishell.h"
#include "../../inc/signals.h"

static void    sig_handler_init(struct sigaction *sigact)
{
	sigemptyset(&(*sigact).sa_mask);
	(*sigact).sa_flags = 0;
	sigaction(SIGINT, sigact, NULL);
	sigaction(SIGQUIT, sigact, NULL);
}

void	sig_handler_exec(int signal)
{
	ft_putendl_fd("Handled Signal?", 2);
	if (signal == SIGINT || signal == SIGQUIT)
	{
		g_signals = signal;
		ft_putendl_fd("Handled Signal!", 2);
		printf("Exec Signal: %d\n", signal);
	}
	else
		printf("UNHANDLED SIGNAL! %d\n", signal);
}

void    update_sig_handler(struct sigaction *sigact, enum e_sig_handle mode)
{
	if (mode == SIG_HANDLE_IDLE)
	{
		(*sigact).sa_handler = sig_handler_idle;
		ft_putendl_fd("Handling Idle!", 2);
	}
	else if (mode == SIG_HANDLE_EXEC)
	{
		(*sigact).sa_handler = sig_handler_exec;
		ft_putendl_fd("Handling Exec!", 2);
	}
	else
	{
		(*sigact).sa_handler = SIG_IGN;
		ft_putendl_fd("Handling None!", 2);
	}
	printf("My PID: %ld\n", (long)getpid());
    sig_handler_init(sigact);
    (void)sig_handler_init;
}
