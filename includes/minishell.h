/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:00:00 by britela-          #+#    #+#             */
/*   Updated: 2026/03/26 18:24:05 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/libft.h"

/* Variable globale pour les signaux (une seule autorisée) */
extern int	g_exit_status;

/* ============== ENUMS ============== */

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND
}	t_token_type;

/* ============== STRUCTURES ============== */

typedef struct s_token
{
	char			*value;
	t_token_type	type;
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

/* ============== PARSING ============== */

/* ps1.c */
void	ft_ps1(void);

/* args.c */
t_list	*ft_lexer(char *line);
int		ft_space(char *str, int index);
int		ft_word(char *str, int index);

/* tokens.c */
t_token	*ft_create_token(char *value, int type);
int		ft_get_op_type(char *str, int index);
int		ft_operateur(char *str, int index);
void	ft_print_tokens(t_list *list);

/* quotes.c */
int		ft_check_quotes(char *str);
char	*ft_remove_quotes(char *str);

/* expand.c */
char	*ft_expand_str(char *str);
char	*ft_get_var_value(char *str, int start, int len);
int		ft_var_len(char *str, int start);
int		ft_is_dollar(char *str);

/* expand_utils.c */
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_addchar(char *str, char c);

/* syntax.c */
int		ft_check_syntax(t_list *list);

/* error.c */
void	ft_error_token(char *token);
void	ft_error_newline(void);
void	ft_error_quote(void);

/* parser.c */
t_cmd	*ft_create_cmd(void);
t_cmd	*ft_parse_cmd(t_list **list);
t_cmd	*ft_parser(t_list *list);

/* parser2.c */
void	ft_redir(t_cmd *cmd, t_list **list);
char	**ft_add_word(char **args, char *word);

/* ============== EXEC ============== */

/* exec.c */
int		ft_execute(t_cmd *cmds);

/* exec_simple.c */
int		ft_exec_simple(t_cmd *cmd);

/* exec_pipeline.c */
int		ft_exec_pipeline(t_cmd *cmds);

/* exec_redir.c */
int		ft_apply_redirections(t_cmd *cmd);
int		ft_open_infile(t_cmd *cmd);
int		ft_open_outfile(t_cmd *cmd);

/* exec_heredoc.c */
int		ft_handle_heredoc(t_cmd *cmd);

/* exec_path.c */
char	*ft_find_path(char *cmd);
char	**ft_get_path_dirs(void);
void	ft_free_split(char **split);

/* exec_cmd.c */
void	ft_exec_cmd(t_cmd *cmd);

/* ============== BUILTINS ============== */

/* builtins.c */
int		ft_is_builtin(char *name);
int		ft_run_builtin(t_cmd *cmd);

/* builtin_echo.c */
int		ft_builtin_echo(t_cmd *cmd);

/* builtin_cd.c */
int		ft_builtin_cd(t_cmd *cmd);

/* builtin_pwd.c */
int		ft_builtin_pwd(void);

/* builtin_env.c */
int		ft_builtin_env(void);

/* builtin_export.c */
int		ft_builtin_export(t_cmd *cmd);

/* builtin_unset.c */
int		ft_builtin_unset(t_cmd *cmd);

/* builtin_exit.c */
int		ft_builtin_exit(t_cmd *cmd);

/* ============== SIGNALS ============== */

/* signals.c */
void	ft_setup_signals(void);
void	ft_signal_handler(int sig);
void	ft_signal_heredoc(void);
//void	rl_replace_line(const char *text, int clear_undo);


/* ============== UTILS ============== */

/* free.c */
void	ft_free_cmd(t_cmd *cmd);
void	ft_free_tokens(t_list *list);

#endif
