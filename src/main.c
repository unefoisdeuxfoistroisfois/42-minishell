/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 08:31:07 by britela-          #+#    #+#             */
/*   Updated: 2026/03/25 14:22:49 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc == 1)
	{
		ft_setup_signals();
		while (1)
		{
			ft_ps1();
		}
		return (0);
	}
	return (-1);
}