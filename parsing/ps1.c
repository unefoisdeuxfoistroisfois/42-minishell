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
<<<<<<< HEAD

	if (ft_check_quotes(line) == 1)
  	{
  		printf("minishell: syntax error: unclosed quote\n");
  		free(line);
  		return ;
  	}
=======
	
	if (ft_check_quotes(line) == 1)
	{
  		printf("minishell: syntax error: unclosed quote\n");
  		free(line);
  		return ;
	}
>>>>>>> 1ad3797fd6df204c0eddbf2e9f594646d3b35d2c
  	tokens = ft_lexer(line);
	// debut de la lecture de notre commande
	tokens = ft_lexer(line);
	ft_print_tokens(tokens);
	free(line);
}