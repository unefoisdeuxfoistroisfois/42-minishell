#include "minishell.h"

int	ft_builtin_cd(t_cmd *cmd)
{
	char	*target;

	target = cmd->args[1];
	if (!target)
	{
		target = getenv("HOME");
		if (!target)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	if (chdir(target) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(target);
		return (1);
	}
	return (0);
}
