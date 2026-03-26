/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oussama <oussama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:00:00 by oussama           #+#    #+#             */
/*   Updated: 2026/03/26 12:00:00 by oussama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** pwd
** Affiche le répertoire courant
*/
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
