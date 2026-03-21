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
    	}
		if (ft_operateur(str, index) != 0 && quote == 0)
    	{
			bool = 0;
    	}
		index++;
	}
	return (index);
}

t_list	*ft_lexer(char *line)
{
	t_list  *list;
	t_list  *node;
	t_token *token;
	char *tmp;
	char  *value;
	int i;
	int startword;
	int op_size;
	int	bool;

	list = NULL;
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
			token = ft_create_token(value, ft_get_op_type(line, i));
			node = ft_lstnew(token);
			ft_lstadd_back(&list, node);
			i = i + op_size;
		}
		else
		{
			startword = i;
			i = ft_word(line, i);
			value = ft_substr(line, startword, i - startword);
			tmp = value;
			value = ft_remove_quotes(value);
			free(tmp);
			token = ft_create_token(value, WORD);
			node = ft_lstnew(token);
			ft_lstadd_back(&list, node);
		}
	}
	return (list);
}
