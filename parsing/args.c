#include "minishell.h"

int	ft_space(char *str, int index)
{
	while (str[index] == 32)
	{
		index++;
	}
	return (index);
}

int	ft_word(char *str, int index)
{
	char  quote;
	int bool;

	quote = 0;
	bool = 1;
	while (str[index] != '\0' && bool == 1)
	{
		if ((str[index] == '\'' || str[index] == '"') && quote == 0)
    	{
			quote = str[index];
    	}
		else if (str[index] == quote)
    	{
			quote = 0;
    	}
		if (str[index] == ' ' && quote == 0)
    	{
			bool = 0;
<<<<<<< HEAD
		}
		if (ft_operateur(str, index) != 0 && quote == 0)
		{
			bool = 0;
		}
=======
    	}
		if (ft_operateur(str, index) != 0 && quote == 0)
    	{
			bool = 0;
    	}
>>>>>>> 1ad3797fd6df204c0eddbf2e9f594646d3b35d2c
		index++;
	}
	return (index);
}

t_list	*ft_lexer(char *line)
{
	t_list  *tokens;
	t_list  *node;
	t_token *tok;
	char *tmp;
	char  *value;
	int i;
	int startword;
	int op_size;
	int	bool;

	tokens = NULL;
	i = 0;
	bool = 1;
	while (line[i] != '\0' && bool == 1)
	{
		i = ft_space(line, i);
		if (line[i] == '\0')
			bool = 0;
		op_size = ft_operateur(line, i);
		if (op_size != 0)
		{
			value = ft_substr(line, i, op_size);
			tok = ft_create_token(value, ft_get_op_type(line, i));
			node = ft_lstnew(tok);
			ft_lstadd_back(&tokens, node);
			i = i + op_size;
		}
		else
		{
			startword = i;
			i = ft_word(line, i);
			value = ft_substr(line, startword, i - startword);
      		tmp = value;
      		value = ft_remove_quotes(value);  // ajoute cette ligne
      		free(tmp);
			tok = ft_create_token(value, WORD);
			node = ft_lstnew(tok);
			ft_lstadd_back(&tokens, node);
		}
	}
	return (tokens);
}
