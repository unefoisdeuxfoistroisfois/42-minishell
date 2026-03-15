#include "minishell.h"

int	g_signal = 0;

void	ft_handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = sig;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	ft_setup_signals(void)
{
	signal(SIGINT, ft_handle_signal);
	signal(SIGQUIT, SIG_IGN);
}
