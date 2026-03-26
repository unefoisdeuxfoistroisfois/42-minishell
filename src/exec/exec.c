/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:00:00 by oussama           #+#    #+#             */
/*   Updated: 2026/03/26 12:00:00 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Point d'entrée de l'exécution
** - Si une seule commande → exec_simple
** - Si plusieurs commandes (pipes) → exec_pipeline
*/
int	ft_execute(t_cmd *cmds)
{
	if (!cmds)
		return (0);
	if (cmds->next)
		return (ft_exec_pipeline(cmds));
	return (ft_exec_simple(cmds));
}
