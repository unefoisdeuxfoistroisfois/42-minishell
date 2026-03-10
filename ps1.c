#include "minishell.h"

void	ft_ps1()
{
	char	*line;
  t_list *tokens;

	line = readline("minibiendur$ ");
	if (line == NULL)
	{
		return ;
	}
	if (line[0] != '\0')
	{
		add_history(line);
	}
	// debut de la lecture de notre commande
	tokens = ft_lexer(line);
	ft_print_tokens(tokens);
	free(line);
}
