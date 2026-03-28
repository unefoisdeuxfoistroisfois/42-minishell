/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouamarko <ouamarko@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 09:03:58 by ouamarko          #+#    #+#             */
/*   Updated: 2026/03/14 16:41:12 by ouamarko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_numeric(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_builtin_exit(t_cmd *cmd)
{
	int	code;

	ft_putstr_fd("exit\n", 1);
	code = g_exit_status;
	if (cmd->args[1])
	{
		if (!ft_is_numeric(cmd->args[1]))
		{
			ft_putstr_fd("minibiendur: exit: ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(2);
		}
		if (cmd->args[2])
		{
			ft_putstr_fd("minibiendur: exit: too many arguments\n", 2);
			return (1);
		}
		code = ft_atoi(cmd->args[1]);
	}
	exit(code % 256);
}
