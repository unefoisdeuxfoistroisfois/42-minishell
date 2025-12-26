#include "minishell.h"

//fonctions pour ajouter token + free
t_token *token_new(token_type type, char *value)
{
	t_token *token;

	token = malloc(sizeof(*token));
	if (!token)
	{
		free(value);
		return (NULL);
	}
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void free_tokens(t_token *lst)
{
	t_token *tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->value);
		free(lst);
		lst = tmp;
	}
}
