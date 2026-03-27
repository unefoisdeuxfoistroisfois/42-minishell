#include "minishell.h"

extern char	**environ;

int	ft_builtin_env(void)
{
	int	i;

	if (!environ)
		return (0);
	i = 0;
	while (environ[i])
	{
		ft_putstr_fd(environ[i], 1);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
