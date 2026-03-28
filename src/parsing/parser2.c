/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:03:46 by britela-          #+#    #+#             */
/*   Updated: 2026/03/28 21:59:48 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_add_word(char **args, char *word)
{
	char	**new_args;
	int		count;
	int		i;

	count = 0;
	if (args != NULL)
	{
		while (args[count] != NULL)
			count++;
	}
	new_args = malloc(sizeof(char *) * (count + 2));
	if (new_args == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[i] = ft_strdup(word);
	new_args[i + 1] = NULL;
	if (args != NULL)
		free(args);
	return (new_args);
}

void	ft_set_redir(t_cmd *cmd, t_token *token, t_token *next_token)
{
	if (token->type == REDIR_IN)
		cmd->infile = ft_strdup(next_token->value);
	else if (token->type == REDIR_OUT)
	{
		cmd->outfile = ft_strdup(next_token->value);
		cmd->append = 0;
	}
	else if (token->type == APPEND)
	{
		cmd->outfile = ft_strdup(next_token->value);
		cmd->append = 1;
	}
	else if (token->type == HEREDOC)
	{
		cmd->delimiter = ft_strdup(next_token->value);
		cmd->heredoc = 1;
	}
}

void	ft_redir(t_cmd *cmd, t_list **list)
{
	t_token	*token;
	t_token	*next_token;

	token = (t_token *)(*list)->content;
	*list = (*list)->next;
	if (*list == NULL)
		return ;
	next_token = (t_token *)(*list)->content;
	ft_set_redir(cmd, token, next_token);
	*list = (*list)->next;
}
