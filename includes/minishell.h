#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/libft.h" //le chemin que le minishell.h doit faire pour trouvé l'indclude de libft

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
t_list  *ft_lexer(char *line);
int	ft_space(char *str, int index);
int	ft_word(char *str, int index);
void	ft_print_tokens(t_list *list);

// tokens.c
t_token	*ft_create_token(char *value, int type);
int		ft_get_op_type(char *str, int index);
int		ft_operateur(char *str, int index);
void	ft_print_tokens(t_list *tokens);

// quotes.c
char	*ft_remove_quotes(char *str);
int	ft_check_quotes(char *str);

// expand.c
int ft_is_dollar(char *str);
int	ft_var_len(char *str, int start);

#endif
