/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:00:00 by oussama           #+#    #+#             */
/*   Updated: 2026/03/26 12:00:00 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Libère un tableau de strings
*/
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

/*
** Récupère les dossiers du PATH
** Retourne un tableau de strings ["usr/bin", "/bin", ...]
*/
char	**ft_get_path_dirs(void)
{
	char	*path_env;
	char	**dirs;

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	return (dirs);
}

/*
** Construit le chemin complet : /usr/bin/ls
*/
static char	*ft_build_path(char *dir, char *cmd)
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

/*
** Cherche la commande dans les dossiers du PATH
** Retourne le chemin complet si trouvé, NULL sinon
*/
char	*ft_find_path(char *cmd)
{
	char	**dirs;
	char	*path;
	int		i;

	if (!cmd || !cmd[0])
		return (NULL);
	dirs = ft_get_path_dirs();
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
