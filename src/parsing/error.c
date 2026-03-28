/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:54:42 by britela-          #+#    #+#             */
/*   Updated: 2026/03/28 21:59:51 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_token(char *token)
{
	printf ("minibiendur: syntax error near unexpected token `%s'\n", token);
}

void	ft_error_newline(void)
{
	printf ("minibiendur: syntax error near unexpected token `newline'\n");
}

void	ft_error_quote(void)
{
	printf ("minibiendur: syntax error: unclosed quote\n");
}
