/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:12:58 by britela-          #+#    #+#             */
/*   Updated: 2025/12/25 19:39:36 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "Libft/libft.h"

// catégories de token
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND
} token_type;

typedef struct s_token
{
	token_type	type;
	char	*value;
	struct s_token	*next;
} t_token;

// ps1.c
void	ft_ps1();

// args.c
t_token	*ft_lexer(char *line);
int	ft_space(char *str, int index);
int	ft_word(char *str, int index);

/* token.c */
t_token *token_new(token_type type, char *value);
void token_add_back(t_token **lst, t_token *new);
void free_tokens(t_token *lst);

#endif
