#include "minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	ft_setup_signals();
	while (1)
	{
		ft_ps1();
	}
	return (0);
}