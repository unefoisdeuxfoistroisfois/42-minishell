#include "minishell.h"

void	ft_error_token(char *token)
{
	printf ("minibiendur: syntax error near unexpected token `%s'\n", token);
}

void	ft_error_newline(void)
{
	printf ("minibiendur: syntax error near unexpected token `newline'\n");
}

void	ft_error_quote(void)
{
	printf ("minibiendur: syntax error: unclosed quote\n");
}
