/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouamarko <ouamarko@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 10:14:22 by ouamarko          #+#    #+#             */
/*   Updated: 2026/03/11 14:32:07 by ouamarko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_cd(t_cmd *cmd)
{
	char	*target;

	target = cmd->args[1];
	if (!target)
	{
		target = getenv("HOME");
		if (!target)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	if (chdir(target) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(target);
		return (1);
	}
	return (0);
}
