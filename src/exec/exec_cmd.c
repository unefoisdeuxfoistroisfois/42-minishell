/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouamarko <ouamarko@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:55:26 by ouamarko          #+#    #+#             */
/*   Updated: 2026/03/28 19:41:21 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_error(char *cmd, int code)
{
	ft_putstr_fd("minibiendur: ", 2);
	ft_putstr_fd(cmd, 2);
	if (code == 127)
		ft_putstr_fd(": command not found\n", 2);
	else if (code == 126)
		ft_putstr_fd(": Permission denied\n", 2);
	else
		ft_putstr_fd(": No such file or directory\n", 2);
	exit(code);
}

void	ft_exec_cmd(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (!cmd->args[0])
		exit(0);
	if (ft_apply_redirections(cmd) < 0)
		exit(1);
	if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
	{
		if (access(cmd->args[0], F_OK) < 0)
			ft_cmd_error(cmd->args[0], 127);
		if (access(cmd->args[0], X_OK) < 0)
			ft_cmd_error(cmd->args[0], 126);
		execve(cmd->args[0], cmd->args, shell->env);
		perror("execve");
		exit(126);
	}
	path = ft_find_path(cmd->args[0], shell);
	if (!path)
		ft_cmd_error(cmd->args[0], 127);
	execve(path, cmd->args, shell->env);
	free(path);
	perror("execve");
	exit(126);
}
