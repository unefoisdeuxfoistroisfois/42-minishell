/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:17:39 by britela-          #+#    #+#             */
/*   Updated: 2026/03/25 17:41:16 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_check_pipe(t_token *token, t_token *prev)
{
	if (token->type == PIPE && prev == NULL)
	{
		ft_error_token("|");
		return (1);
	}
	if (token->type == PIPE && prev != NULL && prev->type == PIPE)
	{
		ft_error_token("|");
		return (1);
	}
	return (0);
}

static int	ft_check_redir(t_token *token, t_token *prev)
{
	if (prev != NULL && (prev->type >= REDIR_IN && prev->type <= APPEND))
	{
		if (token->type != WORD)
		{
			ft_error_token(token->value);
			return (1);
		}
	}
	return (0);
}

static int	ft_check_end(t_token *prev)
{
	if (prev != NULL && prev->type != WORD)
	{
		ft_error_newline();
		return (1);
	}
	return (0);
}

int	ft_check_syntax(t_list *list)
{
	t_token	*token;
	t_token	*prev;

	prev = NULL;
	while (list != NULL)
	{
		token = (t_token *)list->content;
		if (ft_check_pipe(token, prev))
			return (1);
		if (ft_check_redir(token, prev))
			return (1);
		prev = token;
		list = list->next;
	}
	if (ft_check_end(prev))
		return (1);
	return (0);
}
