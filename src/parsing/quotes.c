/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 09:11:33 by britela-          #+#    #+#             */
/*   Updated: 2026/03/26 11:34:07 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_check_quotes(char *str)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		i++;
	}
	if (quote != 0)
		return (1);
	return (0);
}

static void	ft_process_char(char *str, int i, char *quote, int *is_quote)
{
	*is_quote = 0;
	if ((str[i] == '\'' || str[i] == '"') && *quote == 0)
	{
		*quote = str[i];
		*is_quote = 1;
	}
	else if (str[i] == *quote)
	{
		*quote = 0;
		*is_quote = 1;
	}
}

char	*ft_remove_quotes(char *str)
{
	char	*result;
	char	quote;
	int		i;
	int		j;
	int		is_quote;

	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (result == NULL)
		return (NULL);
	quote = 0;
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		ft_process_char(str, i, &quote, &is_quote);
		if (!is_quote)
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
