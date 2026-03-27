#include "minishell.h"

extern char	**environ;

static void	ft_print_export(void)
{
	int	i;

	if (!environ)
		return ;
	i = 0;
	while (environ[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(environ[i], 1);
		write(1, "\n", 1);
		i++;
	}
}

static int	ft_env_len(void)
{
	int	i;

	i = 0;
	if (!environ)
		return (0);
	while (environ[i])
		i++;
	return (i);
}

static int	ft_find_env_index(char *name, int name_len)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], name, name_len) == 0
			&& environ[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static int	ft_add_or_update_env(char *arg)
{
	char	**new_env;
	int		i;
	int		len;
	int		name_len;
	int		idx;

	name_len = 0;
	while (arg[name_len] && arg[name_len] != '=')
		name_len++;
	if (arg[name_len] != '=')
		return (0);
	idx = ft_find_env_index(arg, name_len);
	if (idx >= 0)
	{
		free(environ[idx]);
		environ[idx] = ft_strdup(arg);
		return (0);
	}
	len = ft_env_len();
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (1);
	i = -1;
	while (++i < len)
		new_env[i] = environ[i];
	new_env[i] = ft_strdup(arg);
	new_env[i + 1] = NULL;
	environ = new_env;
	return (0);
}

int	ft_builtin_export(t_cmd *cmd)
{
	int	i;
	int	ret;

	if (!cmd->args[1])
	{
		ft_print_export();
		return (0);
	}
	ret = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (ft_add_or_update_env(cmd->args[i]) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}
