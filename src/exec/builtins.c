/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:00:00 by oussama           #+#    #+#             */
/*   Updated: 2026/03/26 18:15:56 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Vérifie si la commande est un builtin
*/
int	ft_is_builtin(char *name)
{
	if (!name)
		return (0);
	if (ft_strncmp(name, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(name, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(name, "export", 7) == 0)
		return (1);
	if (ft_strncmp(name, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(name, "env", 4) == 0)
		return (1);
	if (ft_strncmp(name, "exit", 5) == 0)
		return (1);
	return (0);
}

/*
** Exécute le builtin correspondant
*/
int	ft_run_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (ft_builtin_echo(cmd));
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (ft_builtin_cd(cmd));
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (ft_builtin_pwd());
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (ft_builtin_export(cmd));
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (ft_builtin_unset(cmd));
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (ft_builtin_env());
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (ft_builtin_exit(cmd));
	return (1);
}
