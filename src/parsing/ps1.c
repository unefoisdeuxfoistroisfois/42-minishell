#include "minishell.h"

static int	ft_handle_null_line(char *line)
{
	if (line == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		exit(g_exit_status);
	}
	return (0);
}

static int	ft_handle_quotes_error(char *line)
{
	if (ft_check_quotes(line) == 1)
	{
		ft_error_quote();
		g_exit_status = 2;
		free(line);
		return (1);
	}
	return (0);
}

static int	ft_handle_syntax_error(t_list *list, char *line)
{
	if (ft_check_syntax(list) == 1)
	{
		g_exit_status = 2;
		ft_free_tokens(list);
		free(line);
		return (1);
	}
	return (0);
}

void	ft_ps1(void)
{
	char	*line;
	t_list	*list;
	t_cmd	*cmd;

	line = readline("minibiendur$ ");
	ft_handle_null_line(line);
	if (line[0] != '\0')
		add_history(line);
	if (ft_handle_quotes_error(line))
		return ;
	list = ft_lexer(line);
	if (ft_handle_syntax_error(list, line))
		return ;
	cmd = ft_parser(list);
	ft_execute(cmd);
	ft_free_tokens(list);
	ft_free_cmd(cmd);
	free(line);
}
