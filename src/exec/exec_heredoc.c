/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouamarko <ouamarko@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 16:08:47 by ouamarko          #+#    #+#             */
/*   Updated: 2026/03/18 11:47:03 by ouamarko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_delimiter(char *line, char *delimiter)
{
	int	len;

	if (!line)
		return (1);
	len = ft_strlen(delimiter);
	if (ft_strncmp(line, delimiter, len) == 0)
	{
		if (line[len] == '\0' || line[len] == '\n')
			return (1);
	}
	return (0);
}

void	ft_read_heredoc(int write_fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_is_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
}

int	ft_handle_heredoc(t_cmd *cmd)
{
	int	pipe_fd[2];

	if (!cmd->delimiter)
		return (0);
	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		return (-1);
	}
	ft_read_heredoc(pipe_fd[1], cmd->delimiter);
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[0]);
	return (0);
}