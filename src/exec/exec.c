/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 08:44:19 by ouamarko          #+#    #+#             */
/*   Updated: 2026/03/28 21:59:44 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute(t_cmd *cmds, t_shell *shell)
{
	if (!cmds)
		return (0);
	if (cmds->next)
		return (ft_exec_pipeline(cmds, shell));
	return (ft_exec_simple(cmds, shell));
}
