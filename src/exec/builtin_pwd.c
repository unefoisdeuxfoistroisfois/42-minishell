/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouamarko <ouamarko@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:51:44 by ouamarko          #+#    #+#             */
/*   Updated: 2026/03/12 08:54:36 by ouamarko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_pwd(void)
{
	char	cwd[4096];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("pwd");
		return (1);
	}
	ft_putstr_fd(cwd, 1);
	write(1, "\n", 1);
	return (0);
}
