// le lexer prend notre ligne et la decoupé en token

// FAIT commencé par sauté les espaces
// FAIT detection d'un mot
// FAIT detection d'operateur | < > << >>
// stocker les tockens dans des structure

#include "Libft/libft.h"
#include "minishell.h"

void	ft_print_tokens(t_list *tokens)
{
	t_token	*tok;

	while (tokens != NULL)
	{
		tok = (t_token *)tokens->content;
		printf("type: %d | value: %s\n", tok->type, tok->value);
		tokens = tokens->next;
	}
}

// Création d'un token
t_token *ft_create_token(char *value, int type)
{
  t_token *token;

  token = malloc(sizeof(t_token));
  if (token == NULL)
  {
    return (NULL);
  }
  // attribué les element de notre tokens
  token->value = value;
  token->type = type;

  //retour de notre token apres avoir recu les nouvelles valeurs
  return (token);
}

int	ft_get_op_type(char *str, int index)
{
	if (ft_strncmp(&str[index], "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(&str[index], ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(&str[index], "|", 1) == 0)
		return (PIPE);
	if (ft_strncmp(&str[index], "<", 1) == 0)
		return (REDIR_IN);
	if (ft_strncmp(&str[index], ">", 1) == 0)
		return (REDIR_OUT);
	return (WORD);
}

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

t_list  *ft_lexer(char *line)
{
  t_list  *tokens;
	t_list  *node;
	t_token *tok;
	char  *value;
	int type;
	int i;
	int startword;
	int op_size;
  int bool;

	i = 0;
  bool = 1;
  tokens = NULL;
	while (line[i] != '\0' && bool == 1)
	{
		i = ft_space(line, i);
    if (line[i] == '\0')
    {
      bool = 0;
    }
		op_size = ft_operateur(line, i);
    if (op_size != 0)
    {
      value = ft_substr(line, i, op_size);
			type = ft_get_op_type(line, i);
			tok = ft_create_token(value, type);
			node = ft_lstnew(tok);
			ft_lstadd_back(&tokens, node);
			i = i + op_size;
    }
    else
    {
      startword = i;
			i = ft_word(line, i);
			value = ft_substr(line, startword, i - startword);
			tok = ft_create_token(value, WORD);
			node = ft_lstnew(tok);
			ft_lstadd_back(&tokens, node);
    }
	}
	return (tokens);
}
