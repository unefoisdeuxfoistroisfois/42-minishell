/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:22:14 by britela-          #+#    #+#             */
/*   Updated: 2026/03/28 21:59:52 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_space(char *str, int index)
{
	while (str[index] == 32)
		index++;
	return (index);
}

int	ft_word(char *str, int index)
{
	char	quote;
	int		bool;

	quote = 0;
	bool = 1;
	while (str[index] != '\0' && bool == 1)
	{
		if ((str[index] == '\'' || str[index] == '"') && quote == 0)
			quote = str[index];
		else if (str[index] == quote)
			quote = 0;
		if (str[index] == ' ' && quote == 0)
			bool = 0;
		else if (ft_operateur(str, index) != 0 && quote == 0)
			bool = 0;
		else
			index++;
	}
	return (index);
}

void	ft_add_operator_token(t_list **list, char *line, int *i)
{
	char	*value;
	t_token	*token;
	t_list	*node;
	int		op_size;

	op_size = ft_operateur(line, *i);
	value = ft_substr(line, *i, op_size);
	token = ft_create_token(value, ft_get_op_type(line, *i));
	node = ft_lstnew(token);
	ft_lstadd_back(list, node);
	*i = *i + op_size;
}

void	ft_add_word_token(t_list **list, char *line, int *i, char **env)
{
	char	*value;
	char	*tmp;
	t_token	*token;
	t_list	*node;
	int		start;

	start = *i;
	*i = ft_word(line, *i);
	value = ft_substr(line, start, *i - start);
	tmp = value;
	value = ft_expand_str(value, env);
	free(tmp);
	tmp = value;
	value = ft_remove_quotes(value);
	free(tmp);
	token = ft_create_token(value, WORD);
	node = ft_lstnew(token);
	ft_lstadd_back(list, node);
}

t_list	*ft_lexer(char *line, char **env)
{
	t_list	*list;
	int		i;
	int		bool;

	list = NULL;
	i = 0;
	bool = 1;
	while (line[i] != '\0' && bool == 1)
	{
		i = ft_space(line, i);
		if (line[i] == '\0')
			bool = 0;
		else if (ft_operateur(line, i) != 0)
			ft_add_operator_token(&list, line, &i);
		else
			ft_add_word_token(&list, line, &i, env);
	}
	return (list);
}
