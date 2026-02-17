#include "minishell.h"

void	ft_ps1()
{
	char	*line;

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
	ft_lexer(line);
	free(line);
}
