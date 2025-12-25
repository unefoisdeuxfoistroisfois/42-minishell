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
		if (ft_strcmp(&str[index], taboperateur[j], size) == 0);
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

void	ft_lexer(char *line)
{
	int	i;
	int	startword;

	i = 0;
	while (line[i] != '\0')
	{
		i = ft_space(line, i);
		ft_operateur(line, i);

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
	}
}
