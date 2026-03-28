/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouamarko <ouamarko@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:29:02 by ouamarko          #+#    #+#             */
/*   Updated: 2026/03/28 19:41:21 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_env(char *name, t_shell *shell)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0
			&& shell->env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_remove_env(int idx, t_shell *shell)
{
	free(shell->env[idx]);
	while (shell->env[idx + 1])
	{
		shell->env[idx] = shell->env[idx + 1];
		idx++;
	}
	shell->env[idx] = NULL;
}

int	ft_builtin_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	idx;

	i = 1;
	while (cmd->args[i])
	{
		idx = ft_find_env(cmd->args[i], shell);
		if (idx >= 0)
			ft_remove_env(idx, shell);
		i++;
	}
	return (0);
}
