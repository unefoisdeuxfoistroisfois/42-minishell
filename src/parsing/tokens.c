#include "minishell.h"

t_token	*ft_create_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
	{
		return (NULL);
	}
	token->value = value;
	token->type = type;
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
