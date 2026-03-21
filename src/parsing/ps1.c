#include "minishell.h"

void	ft_ps1()
{
	char	*line;
	t_list	*tokens;
	t_token	*tok;

	line = readline("minibiendur$ ");
	if (line == NULL)
	{
		return ;
	}
	if (line[0] != '\0')
	{
		add_history(line);
	}

	if (ft_check_quotes(line) == 1)
  	{
  		printf("minishell: syntax error: unclosed quote\n");
  		free(line);
  		return ;
  	}
	// debut de la lecture de notre commande
	tokens = ft_lexer(line);
	tok = (t_token *)tokens->content;
	if (ft_is_dollar(tok->value) == 1)
		printf("Dollar trouvé!\n");
	ft_print_tokens(tokens);
	free(line);
}