CC = cc
NAME = minishell
SRC = main.c ps1.c args.c
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

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$$LOGO"
	@echo "\033[1;32mLIASON DES OBJETS\033[0m"
	$(CC) $(OBJ) $(CFLAGS) -o $@ -lreadline

# .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean 
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
