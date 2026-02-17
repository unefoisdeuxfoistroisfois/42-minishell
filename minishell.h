#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "Libft/libft.h"

// ps1.c
void	ft_ps1();

// args.c
void	ft_lexer(char *line);
int	ft_space(char *str, int index);
int	ft_word(char *str, int index);

#endif
