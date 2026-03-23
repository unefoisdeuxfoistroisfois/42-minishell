#include "minishell.h"

void	ft_ps1()
{
	char	*line;
	t_list	*list;
	t_token	*token;

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
	list = ft_lexer(line);
	token = (t_token *)list->content;
	if (ft_is_dollar(token->value) == 1)
	{
		printf("Dollar trouvé!\n");
		printf("Longueur var: %d\n", ft_var_len(token->value, 1));  // 1 = après le $
	}
	ft_print_tokens(list);
	free(line);
}