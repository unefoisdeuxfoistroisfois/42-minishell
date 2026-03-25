#include "minishell.h"

void	ft_print_cmd(t_cmd *cmd)
{
	int	i;

	while (cmd != NULL)
	{
		printf("=== CMD ===\n");
		if (cmd->args != NULL)
		{
			i = 0;
			while (cmd->args[i] != NULL)
			{
				printf("args[%d]: %s\n", i, cmd->args[i]);
				i++;
			}
		}
		printf("infile: %s\n", cmd->infile);
		printf("outfile: %s\n", cmd->outfile);
		printf("append: %d\n", cmd->append);
		printf("heredoc: %d\n", cmd->heredoc);
		printf("delimiter: %s\n", cmd->delimiter);
		cmd = cmd->next;
	}
}

void	ft_ps1()
{
	char	*line;
	t_list	*list;
	t_cmd	*cmd;

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
	cmd = ft_parser(list);
	ft_print_cmd(cmd);

	free(line);
}