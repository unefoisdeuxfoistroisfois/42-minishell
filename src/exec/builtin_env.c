/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:00:00 by oussama           #+#    #+#             */
/*   Updated: 2026/03/26 12:00:00 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
