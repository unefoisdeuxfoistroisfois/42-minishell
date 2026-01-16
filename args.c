/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 19:50:51 by britela-          #+#    #+#             */
/*   Updated: 2025/12/25 19:55:06 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// le lexer prend notre ligne et la decoupé en token

//commencé par sauté les espaces
//detection d'un mot
//detection d'operateur | < > << >>

#include "minishell.h"

int	ft_operateur(char *str, int index)
{
	char	*taboperateur[] = {"<<", ">>", "|", "<", ">"};
	int	j;
	int	size;

	j = 0;
	//parcourir mon tableau d'operateur
	while (j < 5)
	{
		size = ft_strlen(taboperateur[j]);
		if (ft_strncmp(&str[index], taboperateur[j], size) == 0)
		{
			return (size);
		}
		j++;
	}
	return (0);
}

int	ft_word(char *str, int index)
{
	while (str[index] != 32 && str[index] != '\0')
	{
		index++;
	}
	return (index);
}

// j'aurais pu utilisé un pointeur mais pas besoin
int	ft_space(char *str, int index)
{
	while (str[index] == 32)
	{
		index++;
	}
	return (index);
}

t_token	*ft_lexer(char *line)
{
	t_token	*token;
	t_token	*new_token;
	int	i;
	int	startword;
	
	token = NULL;
	new_token = NULL;
	i = 0;
	while (line[i] != '\0')
	{
		i = ft_space(line, i);
		if(ft_operateur(line, i) > 0) //si cest un operateur
		{
			if (!token)
				token = new_token = token_new(TOKEN_PIPE, ft_substr(line, i, ft_operateur(line, i)));
			else
			{
				new_token->next = token_new(TOKEN_PIPE, ft_substr(line, i, ft_operateur(line, i)));
				new_token = new_token->next;
			}
			i = i + ft_operateur(line, i);
		}
		else if (line[i] != '\0' && line[i] != ' ') //si cest un mot
		{
			startword = i;
			i = ft_word(line, i);
			if (!token)
				token = new_token = token_new(TOKEN_WORD, ft_substr(line, startword, i - startword));
			else
			{
				new_token->next = token_new(TOKEN_WORD, ft_substr(line, startword, i - startword));
				new_token = new_token->next;
			}
		}
	}
		// on mets un drapeau ou le mot commence 
		startword = i;
		i = ft_word(line, i);
		// si notre i est toujours plus grand grace au nb de lettre lu
		if (startword < i)
		{
			while (startword < i)
			{
				printf("%c", line[startword]);
				startword++;
			}
			printf("\n");
		}
		return(token);
}