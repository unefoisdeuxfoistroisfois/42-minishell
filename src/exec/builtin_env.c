/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:00:00 by oussama           #+#    #+#             */
/*   Updated: 2026/03/26 18:16:00 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

/*
** env
** Affiche toutes les variables d'environnement
*/
int	ft_builtin_env(void)
{
	int	i;

	if (!environ)
		return (0);
	i = 0;
	while (environ[i])
	{
		ft_putstr_fd(environ[i], 1);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
