CC = cc
NAME = minishell
SRC = main.c ps1.c args.c tokens.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g -I.

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

# Variable Libft
LIBFT_DIR   = Libft
LIBFT       = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "$$LOGO"
	@echo "\033[1;32mLIASON DES OBJETS\033[0m"
	$(CC) $(OBJ) $(CFLAGS) -o $@ -L$(LIBFT_DIR) -lft -lreadline

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

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
