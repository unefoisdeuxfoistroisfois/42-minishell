/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:38:17 by ouamarko          #+#    #+#             */
/*   Updated: 2026/03/28 19:41:21 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_export(t_shell *shell)
{
	int	i;

	if (!shell->env)
		return ;
	i = 0;
	while (shell->env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(shell->env[i], 1);
		write(1, "\n", 1);
		i++;
	}
}

int	ft_find_env_index(char *name, int name_len, t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, name_len) == 0
			&& shell->env[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_create_new_env(char *arg, int len, t_shell *shell)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (1);
	i = -1;
	while (++i < len)
		new_env[i] = shell->env[i];
	new_env[i] = ft_strdup(arg);
	if (!new_env[i])
	{
		free(new_env);
		return (1);
	}
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (0);
}

int	ft_add_or_update_env(char *arg, t_shell *shell)
{
	int		name_len;
	int		idx;

	name_len = 0;
	while (arg[name_len] && arg[name_len] != '=')
		name_len++;
	if (arg[name_len] != '=')
		return (0);
	idx = ft_find_env_index(arg, name_len, shell);
	if (idx >= 0)
	{
		free(shell->env[idx]);
		shell->env[idx] = ft_strdup(arg);
		return (0);
	}
	return (ft_create_new_env(arg, ft_env_len(shell), shell));
}

int	ft_builtin_export(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	ret;

	if (!cmd->args[1])
	{
		ft_print_export(shell);
		return (0);
	}
	ret = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (ft_add_or_update_env(cmd->args[i], shell) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}
