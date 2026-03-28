/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 09:05:33 by britela-          #+#    #+#             */
/*   Updated: 2026/03/28 11:44:02 by britela-         ###   ########.fr       */
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

extern int	g_exit_status;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND
}	t_token_type;

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

typedef struct s_shell
{
	char	**env;
}	t_shell;

/* ps1.c */
int		ft_handle_null_line(char *line);
int		ft_handle_quotes_error(char *line);
int		ft_handle_syntax_error(t_list *list, char *line);
void	ft_ps1(t_shell *shell);

/* args.c */
int		ft_space(char *str, int index);
int		ft_word(char *str, int index);
void	ft_add_operator_token(t_list **list, char *line, int *i);
void	ft_add_word_token(t_list **list, char *line, int *i, char **env);
t_list	*ft_lexer(char *line, char **env);

/* tokens.c */
t_token	*ft_create_token(char *value, int type);
int		ft_get_op_type(char *str, int index);
int		ft_operateur(char *str, int index);
void	ft_print_tokens(t_list *list);

/* quotes.c */
int		ft_check_quotes(char *str);
void	ft_process_char(char *str, int i, char *quote, int *is_quote);
char	*ft_remove_quotes(char *str);

/* expand.c */
void	ft_update_quote(char c, char *quote);
char	*ft_expand_var(char *str, int *i, char *result, char **env);
char	*ft_expand_str(char *str, char **env);
char	*ft_get_var_value(char *str, int start, int len, char **env);
int		ft_var_len(char *str, int start);

/* expand_utils.c */
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_addchar(char *str, char c);
int		ft_is_dollar(char *str);

/* syntax.c */
int		ft_check_pipe(t_token *token, t_token *prev);
int		ft_check_redir(t_token *token, t_token *prev);
int		ft_check_end(t_token *prev);
int		ft_check_syntax(t_list *list);

/* error.c */
void	ft_error_token(char *token);
void	ft_error_newline(void);
void	ft_error_quote(void);

/* parser.c */
t_cmd	*ft_parser(t_list *list);
t_cmd	*ft_parse_cmd(t_list **list);
t_cmd	*ft_create_cmd(void);

/* parser2.c */
char	**ft_add_word(char **args, char *word);
void	ft_set_redir(t_cmd *cmd, t_token *token, t_token *next_token);
void	ft_redir(t_cmd *cmd, t_list **list);

/* free.c */
void	ft_free_args(char **args);
void	ft_free_cmd_fields(t_cmd *cmd);
void	ft_free_cmd(t_cmd *cmd);
void	ft_free_token(t_token *token);
void	ft_free_tokens(t_list *list);

/* exec.c */
int		ft_execute(t_cmd *cmds, t_shell *shell);

/* exec_simple.c */
int		ft_exec_simple(t_cmd *cmd, t_shell *shell);

/* exec_pipeline.c */
void	ft_pipe_child(t_cmd *cmd, int input_fd, int *pipe_fd, t_shell *shell);
int		ft_fork_pipe_cmd(t_cmd *cmd, int input_fd,
			int *pipe_fd, t_shell *shell);
int		ft_wait_all(void);
int		ft_exec_pipeline(t_cmd *cmds, t_shell *shell);

/* exec_redir.c */
int		ft_open_infile(t_cmd *cmd);
int		ft_open_outfile(t_cmd *cmd);
int		ft_apply_redirections(t_cmd *cmd);

/* exec_heredoc.c */
int		ft_is_delimiter(char *line, char *delimiter);
void	ft_read_heredoc(int write_fd, char *delimiter);
int		ft_handle_heredoc(t_cmd *cmd);

/* exec_path.c */
void	ft_free_split(char **split);
char	**ft_get_path_dirs(t_shell *shell);
char	*ft_build_path(char *dir, char *cmd);
char	*ft_find_path(char *cmd, t_shell *shell);

/* exec_cmd.c */
void	ft_cmd_error(char *cmd, int code);
void	ft_exec_cmd(t_cmd *cmd, t_shell *shell);

/* builtins.c */
int		ft_is_builtin(char *name);
int		ft_run_builtin(t_cmd *cmd, t_shell *shell);

/* builtin_echo.c */
int		ft_is_n_flag(char *arg);
int		ft_builtin_echo(t_cmd *cmd);

/* builtin_cd.c */
int		ft_builtin_cd(t_cmd *cmd, t_shell *shell);

/* builtin_pwd.c */
int		ft_builtin_pwd(void);

/* builtin_env.c */
char	*ft_getenv(char *name, char **env);
int		ft_env_len(t_shell *shell);
int		ft_builtin_env(t_shell *shell);

/* builtin_export.c */
void	ft_print_export(t_shell *shell);
int		ft_find_env_index(char *name, int name_len, t_shell *shell);
int		ft_create_new_env(char *arg, int len, t_shell *shell);
int		ft_add_or_update_env(char *arg, t_shell *shell);
int		ft_builtin_export(t_cmd *cmd, t_shell *shell);

/* builtin_unset.c */
int		ft_find_env(char *name, t_shell *shell);
void	ft_remove_env(int idx, t_shell *shell);
int		ft_builtin_unset(t_cmd *cmd, t_shell *shell);

/* builtin_exit.c */
int		ft_is_numeric(char *str);
int		ft_builtin_exit(t_cmd *cmd);

/* signals.c */
void	ft_signal_handler(int sig);
void	ft_setup_signals(void);
void	ft_signal_heredoc(void);
/*void	rl_replace_line(const char *text, int clear_undo);*/

#endif
