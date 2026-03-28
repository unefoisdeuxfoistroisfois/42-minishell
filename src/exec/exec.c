/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouamarko <ouamarko@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 08:44:19 by ouamarko          #+#    #+#             */
/*   Updated: 2026/03/10 09:31:55 by ouamarko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute(t_cmd *cmds)
{
	if (!cmds)
		return (0);
	if (cmds->next)
		return (ft_exec_pipeline(cmds));
	return (ft_exec_simple(cmds));
}
