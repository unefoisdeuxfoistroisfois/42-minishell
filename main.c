/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:12:28 by britela-          #+#    #+#             */
/*   Updated: 2025/12/22 21:18:48 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int argc, char **argv)
{
	int	ninfini;
	(void)argc;
	(void)argv;

	ninfini = 1;
	while(ninfini)
	{
		ft_ps1();
	}
	return (0);
}
