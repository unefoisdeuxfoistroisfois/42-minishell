/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:00:00 by oussama           #+#    #+#             */
/*   Updated: 2026/03/26 12:00:00 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** unset [NAME...]
** Supprime les variables d'environnement
** Note: unsetenv() n'est pas autorisé, il faudra gérer manuellement
*/
int	ft_builtin_unset(t_cmd *cmd)
{
	(void)cmd;
	/* TODO: Implémenter la suppression de variables
	** Sans unsetenv, il faut:
	** 1. Trouver la variable dans environ
	** 2. Décaler toutes les variables suivantes
	*/
	return (0);
}
