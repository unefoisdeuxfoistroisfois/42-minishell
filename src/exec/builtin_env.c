/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouamarko <ouamarko@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:22:31 by ouamarko          #+#    #+#             */
/*   Updated: 2026/03/13 11:05:29 by ouamarko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_len(void)
{
	int	i;

	i = 0;
	if (!environ)
		return (0);
	while (environ[i])
		i++;
	return (i);
}

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
