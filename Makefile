CC = cc
NAME = minishell
SRC = src/main.c \
      src/parsing/ps1.c \
      src/parsing/args.c \
      src/parsing/tokens.c \
      src/parsing/quotes.c \
      src/parsing/expand.c \
	  src/parsing/expand_utils.c \
	  src/parsing/syntax.c \
	  src/parsing/error.c \
	  src/parsing/parser.c \
	  src/parsing/parser2.c \
	  src/exec/exec.c \
      src/exec/exec_simple.c \
      src/exec/exec_pipeline.c \
      src/exec/exec_cmd.c \
      src/exec/exec_path.c \
      src/exec/exec_redir.c \
      src/exec/exec_heredoc.c \
      src/exec/builtins.c \
      src/exec/builtin_echo.c \
      src/exec/builtin_cd.c \
      src/exec/builtin_pwd.c \
      src/exec/builtin_env.c \
      src/exec/builtin_export.c \
      src/exec/builtin_unset.c \
      src/exec/builtin_exit.c \
      src/exec/signals.c

OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g -I./includes
RM = rm -rf

define LOGO

\033[1;38;5;208m
               ░██           ░██           ░██                   ░██ ░██
                                           ░██                   ░██ ░██
░█████████████ ░██░████████  ░██ ░███████  ░████████   ░███████  ░██ ░██
░██   ░██  ░██ ░██░██    ░██ ░██░██        ░██    ░██ ░██    ░██ ░██ ░██
░██   ░██  ░██ ░██░██    ░██ ░██ ░███████  ░██    ░██ ░█████████ ░██ ░██
░██   ░██  ░██ ░██░██    ░██ ░██       ░██ ░██    ░██ ░██        ░██ ░██
░██   ░██  ░██ ░██░██    ░██ ░██ ░███████  ░██    ░██  ░███████  ░██ ░██
\033[0m

endef
export LOGO

# Libft
LIBFT_DIR   = Libft
LIBFT       = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) 
	@echo "$$LOGO"
	@echo "\033[1;32mLIASON DES OBJETS\033[0m"
	$(CC) $(OBJ) $(CFLAGS) -o $@  $(LIBFT) -lreadline

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR) bonus

# .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJ)

fclean: clean 
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
