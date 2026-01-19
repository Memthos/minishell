OBJS_DIR=objs/
SRCS_DIR=srcs/
INCLUDES_DIR=includes/
SRCS=minishell.c
OBJECTS=$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
LIBFT_DIR=libs/libft_tools/
LIBFT=$(addprefix $(LIBFT_DIR), libft.a)
CFLAGS=-Werror -Wall -Wextra -I$(INCLUDES_DIR) -g
CC=cc
NAME=minishell

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "Finished compiling Minishell"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(LIBFT):
	@make -sC $(LIBFT_DIR) all
	@echo "Compiled library Libft"

clean:
	@rm -drf $(OBJS_DIR)
	@make -sC $(LIBFT_DIR) clean
	@echo "Cleaned Minishell object files"

fclean: clean
	@rm -f $(NAME)
	@make -sC $(LIBFT_DIR) fclean
	@echo "Cleaned Minishell"

re: clean all
	@echo "Recompiled Minishell"

.PHONY: all clean fclean re
