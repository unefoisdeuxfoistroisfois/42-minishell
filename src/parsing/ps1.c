#include "minishell.h"

void	ft_ps1()
{
	char	*line;
	t_list	*list;

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
		ft_error_quote();
  		free(line);
  		return ;
  	}
	// debut de la lecture de notre commande
	list = ft_lexer(line);
	if (ft_check_syntax(list) == 1)
	{
		free(line);
		return ;
	}
	ft_print_tokens(list);
	free(line);
}