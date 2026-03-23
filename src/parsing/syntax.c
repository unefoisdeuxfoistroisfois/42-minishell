#include "minishell.h"

int	ft_check_syntax(t_list *list)
{
	t_token	*token;
	t_token	*prev;

	prev = NULL;
	while (list != NULL)
	{
		token = (t_token *)list->content;
		// Si pipe
		if (token->type == PIPE && prev == NULL)
		{
			ft_error_token("|");
			return (1);
		}
		// Si double pipe
		if (token->type == PIPE && prev != NULL && prev->type == PIPE)
		 {
			ft_error_token("|");
			return (1);
		 }
		// Redir sans fichier après
		if (prev != NULL && (prev->type >= REDIR_IN && prev->type <= APPEND))
		{
			if (token->type != WORD)
			{
				ft_error_token(token->value);
				return (1);
			}
		}
		prev = token;
		list = list->next;
	}
	// Pipe ou redir à la fin
	if (prev != NULL && prev->type != WORD)
	{
		ft_error_newline();
		return (1);
	}
	return (0);
}