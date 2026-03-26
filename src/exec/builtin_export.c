/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
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
** Affiche les variables en format "declare -x VAR="value""
*/
static void	ft_print_export(void)
{
	int	i;

	if (!environ)
		return ;
	i = 0;
	while (environ[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(environ[i], 1);
		write(1, "\n", 1);
		i++;
	}
}

/*
** export [NAME=value]
** Sans argument → affiche les variables
** Avec argument → ajoute/modifie la variable
** Note: setenv() n'est pas autorisé, il faudra gérer manuellement
*/
int	ft_builtin_export(t_cmd *cmd)
{
	if (!cmd->args[1])
	{
		ft_print_export();
		return (0);
	}
	/* TODO: Implémenter l'ajout de variables
	** Sans setenv, il faut:
	** 1. Copier environ dans un nouveau tableau
	** 2. Ajouter la nouvelle variable
	** 3. Remplacer environ par le nouveau tableau
	*/
	return (0);
}
