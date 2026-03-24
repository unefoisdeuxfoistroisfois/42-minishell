#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include "Libft/libft.h"

extern int	g_signal;
extern char	**environ;

typedef enum e_token_type
{
	TOKEN_CMD,
	TOKEN_ARG,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

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


void	ft_ps1(void);
char	*ft_expand_vars(const char *s);
void	ft_setup_signals(void);
t_token	*ft_tokenize(char *line);
t_cmd	*ft_parse(t_token *tokens);
void	ft_free_tokens(t_token *tokens);
void	ft_free_cmds(t_cmd *cmds);
int		ft_execute(t_cmd *cmds);
int		ft_apply_redirections(t_cmd *cmd);
int		ft_execute_pipeline(t_cmd *cmds);
int		ft_is_builtin(char *name);
int		ft_run_builtin(t_cmd *cmd);

#endif
