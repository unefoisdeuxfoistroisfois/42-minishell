#include "minishell.h"

void	ft_ps1(void)
{
	char	*line;
	t_list	*list;
	t_cmd	*cmd;

	line = readline("minibiendur$ ");
	if (line == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		exit(g_exit_status);
	}
	if (line[0] != '\0')
		add_history(line);
	if (ft_check_quotes(line) == 1)
	{
		ft_error_quote();
		g_exit_status = 2;
		free(line);
		return ;
	}
	list = ft_lexer(line);
	if (ft_check_syntax(list) == 1)
	{
		g_exit_status = 2;
		free(line);
		return ;
	}
	cmd = ft_parser(list);
	ft_execute(cmd);
	free(line);
}