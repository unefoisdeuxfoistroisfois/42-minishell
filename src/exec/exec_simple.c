/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:00:00 by oussama           #+#    #+#             */
/*   Updated: 2026/03/26 18:15:51 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

/*
** Exécute une commande simple (sans pipe)
** - Gère le heredoc si nécessaire
** - Builtin → exécute dans le processus parent
** - Externe → fork + execve
*/
int	ft_exec_simple(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (cmd->heredoc)
	{
		if (ft_handle_heredoc(cmd) < 0)
			return (1);
	}
	if (ft_is_builtin(cmd->args[0]))
	{
		if (ft_apply_redirections(cmd) < 0)
			return (1);
		return (ft_run_builtin(cmd));
	}
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
		ft_exec_cmd(cmd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
	return (g_exit_status);
}
