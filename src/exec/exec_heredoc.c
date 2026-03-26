/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:00:00 by oussama           #+#    #+#             */
/*   Updated: 2026/03/26 12:00:00 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Vérifie si la ligne correspond au délimiteur
*/
static int	ft_is_delimiter(char *line, char *delimiter)
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

/*
** Lit les lignes jusqu'au délimiteur et écrit dans le pipe
*/
static void	ft_read_heredoc(int write_fd, char *delimiter)
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

/*
** Gère le heredoc
** << delimiter
** Lit l'input jusqu'au delimiter et redirige vers stdin
*/
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
