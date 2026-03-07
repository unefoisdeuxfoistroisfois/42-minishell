// le lexer prend notre ligne et la decoupé en token

// FAIT commencé par sauté les espaces
// FAIT detection d'un mot
// FAIT detection d'operateur | < > << >>
// stocker les tockens dans des structure

#include "minishell.h"

int	ft_operateur(char *str, int index)
{
  if (ft_strncmp(&str[index], "<<", 2) == 0)
		return (2);
	if (ft_strncmp(&str[index], ">>", 2) == 0)
		return (2);
	if (ft_strncmp(&str[index], "|", 1) == 0)
		return (1);
	if (ft_strncmp(&str[index], "<", 1) == 0)
		return (1);
	if (ft_strncmp(&str[index], ">", 1) == 0)
		return (1);
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
  int op_size;

	i = 0;
	while (line[i] != '\0')
	{
		i = ft_space(line, i);
    if (line[i] == '\0')
    {
      return ;
    }
		op_size = ft_operateur(line, i);
    if (op_size != 0)
    {
      // c'est un op
			printf("op : %.*s\n", op_size, &line[i]);
      i = i + op_size;
    }
    else
    {
		  // on mets un drapeau ou le mot commence 
		  startword = i;
		  i = ft_word(line, i);
		  printf("mot : %.*s\n", i - startword, &line[startword]);
    }
	}
}
