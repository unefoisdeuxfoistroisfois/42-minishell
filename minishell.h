#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "Libft/libft.h"

// Les types possible pour un token
typedef enum e_token_type
{
	WORD, // 0
	PIPE, // 1 |
	REDIR_IN, // 2  <
	REDIR_OUT, // 3 >
	HEREDOC, // 4 <<
	APPEND // 5 >>
}	t_token_type;

// Structure pour un token
typedef struct s_token
{
	char			*value;
	t_token_type	type;
} t_token;

// ps1.c
void	ft_ps1();

// args.c
void	ft_lexer(char *line);
int	ft_space(char *str, int index);
int	ft_word(char *str, int index);

#endif
