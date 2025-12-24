/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 19:50:51 by britela-          #+#    #+#             */
/*   Updated: 2025/12/24 22:27:02 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// le lexer prend notre ligne et la decoupé en token

//commencé par sauté les espaces
//detection d'un mot
//detection d'operateur | < > << >>

#include "minishell.h"

int	ft_word(char *str, int index)
{
	while (str[index] != 32 && str[index] != '\0')
	{
		index++;
	}
	return (index);
}

// j'aurais pu utilisé un pointeur mais ppas besoin
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
