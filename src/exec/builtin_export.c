/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouamarko <ouamarko@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:38:17 by ouamarko          #+#    #+#             */
/*   Updated: 2026/03/16 10:27:53 by ouamarko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_export(void)
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

int	ft_find_env_index(char *name, int name_len)
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

int	ft_create_new_env(char *arg, int len)
{
	char	**new_env;
	int		i;

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

int	ft_add_or_update_env(char *arg)
{
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
		environ[idx] = ft_strdup(arg);
		return (0);
	}
	return (ft_create_new_env(arg, ft_env_len()));
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
