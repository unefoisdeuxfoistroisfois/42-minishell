/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouamarko <ouamarko@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:26:35 by ouamarko          #+#    #+#             */
/*   Updated: 2026/03/17 09:12:38 by ouamarko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_restore_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

static int	ft_exec_builtin(t_cmd *cmd)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (ft_apply_redirections(cmd) < 0)
	{
		ft_restore_fds(saved_stdin, saved_stdout);
		return (1);
	}
	g_exit_status = ft_run_builtin(cmd);
	ft_restore_fds(saved_stdin, saved_stdout);
	return (g_exit_status);
}

static int	ft_exec_external(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

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

int	ft_exec_simple(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (cmd->heredoc)
	{
		if (ft_handle_heredoc(cmd) < 0)
			return (1);
	}
	if (ft_is_builtin(cmd->args[0]))
		return (ft_exec_builtin(cmd));
	return (ft_exec_external(cmd));
}
