/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouamarko <ouamarko@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:22:31 by ouamarko          #+#    #+#             */
/*   Updated: 2026/03/28 19:41:21 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *name, char **env)
{
	int	len;
	int	i;

	if (!env || !name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	ft_env_len(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->env)
		return (0);
	while (shell->env[i])
		i++;
	return (i);
}

int	ft_builtin_env(t_shell *shell)
{
	int	i;

	if (!shell->env)
		return (0);
	i = 0;
	while (shell->env[i])
	{
		ft_putstr_fd(shell->env[i], 1);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
