#include "minishell.h"

extern char	**environ;

static int	ft_find_env(char *name)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], name, len) == 0
			&& environ[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	ft_remove_env(int idx)
{
	while (environ[idx])
	{
		environ[idx] = environ[idx + 1];
		idx++;
	}
}

int	ft_builtin_unset(t_cmd *cmd)
{
	int	i;
	int	idx;

	i = 1;
	while (cmd->args[i])
	{
		idx = ft_find_env(cmd->args[i]);
		if (idx >= 0)
			ft_remove_env(idx);
		i++;
	}
	return (0);
}
