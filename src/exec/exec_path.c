/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouamarko <ouamarko@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 08:17:39 by ouamarko          #+#    #+#             */
/*   Updated: 2026/03/28 19:41:21 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**ft_get_path_dirs(t_shell *shell)
{
	char	*path_env;
	char	**dirs;

	path_env = ft_getenv("PATH", shell->env);
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	return (dirs);
}

char	*ft_build_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}

char	*ft_find_path(char *cmd, t_shell *shell)
{
	char	**dirs;
	char	*path;
	int		i;

	if (!cmd || !cmd[0])
		return (NULL);
	dirs = ft_get_path_dirs(shell);
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		path = ft_build_path(dirs[i], cmd);
		if (path && access(path, X_OK) == 0)
		{
			ft_free_split(dirs);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_split(dirs);
	return (NULL);
}
