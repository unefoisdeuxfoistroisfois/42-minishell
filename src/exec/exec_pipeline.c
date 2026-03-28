/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouamarko <ouamarko@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:33:52 by ouamarko          #+#    #+#             */
/*   Updated: 2026/03/15 10:58:14 by ouamarko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe_child(t_cmd *cmd, int input_fd, int *pipe_fd)
{
	if (input_fd != -1)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (cmd->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (cmd->heredoc)
	{
		if (ft_handle_heredoc(cmd) < 0)
			exit(1);
	}
	if (ft_apply_redirections(cmd) < 0)
		exit(1);
	if (ft_is_builtin(cmd->args[0]))
		exit(ft_run_builtin(cmd));
	ft_exec_cmd(cmd);
}

int	ft_fork_pipe_cmd(t_cmd *cmd, int input_fd, int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		ft_pipe_child(cmd, input_fd, pipe_fd);
	return (0);
}

int	ft_wait_all(void)
{
	int		status;
	int		last_status;
	pid_t	pid;

	last_status = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_status = 128 + WTERMSIG(status);
		pid = wait(&status);
	}
	return (last_status);
}

int	ft_exec_pipeline(t_cmd *cmds)
{
	int		pipe_fd[2];
	int		input_fd;
	t_cmd	*cmd;

	input_fd = -1;
	cmd = cmds;
	while (cmd)
	{
		if (cmd->next && pipe(pipe_fd) < 0)
			return (perror("pipe"), 1);
		if (ft_fork_pipe_cmd(cmd, input_fd, pipe_fd) < 0)
			return (1);
		if (input_fd != -1)
			close(input_fd);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			input_fd = pipe_fd[0];
		}
		cmd = cmd->next;
	}
	g_exit_status = ft_wait_all();
	return (g_exit_status);
}
