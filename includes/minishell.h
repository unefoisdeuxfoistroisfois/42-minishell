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

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				append;
	int				heredoc;
	char			*delimiter;
	struct s_cmd	*next;
}	t_cmd;

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
char	*ft_get_var_value(char *str, int start, int len);
char	*ft_expand_str(char *str);

// expand_utlis.c
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_addchar(char *str, char c);

//syntax.c
int	ft_check_syntax(t_list *list);

// error.c
void	ft_error_token(char *token);
void	ft_error_newline(void);
void	ft_error_quote(void);

// parser.c
t_cmd	*ft_create_cmd(void);
t_cmd	*ft_parse_cmd(t_list **list);
t_cmd	*ft_parser(t_list *list);

// parser2.c
void	ft_redir(t_cmd *cmd, t_list **list);
char	**ft_add_word(char **args, char *word);

#endif