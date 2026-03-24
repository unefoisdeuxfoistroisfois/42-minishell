#include "../minishell.h"

static int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (cmd->args[i] && !ft_strncmp(cmd->args[i], "-n", 3))
	{
		newline = 0;
		i++;
	}
	while (cmd->args[i])
	{
		write(1, cmd->args[i], ft_strlen(cmd->args[i]));
		if (cmd->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}

static int	builtin_pwd(void)
{
	char	cwd[4096];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("pwd");
		return (1);
	}
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	return (0);
}

static int	builtin_cd(t_cmd *cmd)
{
	char	*target;

	target = cmd->args[1];
	if (!target)
		target = getenv("HOME");
	if (!target)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
	if (chdir(target) < 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

static int	builtin_env(void)
{
	int	i;

	i = 0;
	while (environ && environ[i])
	{
		write(1, environ[i], ft_strlen(environ[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

static int	builtin_export(t_cmd *cmd)
{
	(void)cmd;
	return (0);
}

static int	builtin_unset(t_cmd *cmd)
{
	(void)cmd;
	return (0);
}

int	ft_is_builtin(char *name)
{
	if (!name)
		return (0);
	if (!ft_strncmp(name, "cd", 3) || !ft_strncmp(name, "echo", 5)
		|| !ft_strncmp(name, "pwd", 4) || !ft_strncmp(name, "export", 7)
		|| !ft_strncmp(name, "unset", 6) || !ft_strncmp(name, "env", 4))
		return (1);
	return (0);
}

int	ft_run_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (!ft_strncmp(cmd->args[0], "echo", 5))
		return (builtin_echo(cmd));
	if (!ft_strncmp(cmd->args[0], "pwd", 4))
		return (builtin_pwd());
	if (!ft_strncmp(cmd->args[0], "cd", 3))
		return (builtin_cd(cmd));
	if (!ft_strncmp(cmd->args[0], "env", 4))
		return (builtin_env());
	if (!ft_strncmp(cmd->args[0], "export", 7))
		return (builtin_export(cmd));
	if (!ft_strncmp(cmd->args[0], "unset", 6))
		return (builtin_unset(cmd));
	return (1);
}
