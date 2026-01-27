VPATH = srcs:srcs/list:srcs/commands:srcs/parser
OBJDIR = objs/
INCLUDES_DIR = includes/

SRCS =	minishell.c \
		init.c \
		lexer.c \
		sighandle.c \
		utils.c \
		lst_new.c \
		lst_add.c \
		lst_remove.c \
		lst_size.c \
		lst_last.c \
		lst_append.c \
		expansion.c

OBJECTS = $(addprefix $(OBJDIR), $(SRCS:.c=.o))

LIBFT_DIR = libs/libft_tools/
LIBFT = $(addprefix $(LIBFT_DIR), libft_tools.a)

LIBS = $(LIBFT) -lreadline

CC = cc
CFLAGS = -Werror -Wall -Wextra -g

NAME = minishell

all: $(NAME)

$(NAME): $(OBJECTS) | $(LIBFT)
	@$(CC) $(CFLAGS) -o $@ $^ -I$(INCLUDES_DIR) $(LIBS)
	@echo "Finished compiling Minishell"

$(OBJDIR)%.o: %.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(LIBFT):
	@make -sC $(LIBFT_DIR) all
	@echo "Compiled library Libft"

$(OBJDIR) :
	@mkdir -p $(OBJDIR)

clean:
	@rm -drf $(OBJDIR)
	@make -sC $(LIBFT_DIR) clean
	@echo "Cleaned Minishell object files"

fclean: clean
	@rm -f $(NAME)
	@make -sC $(LIBFT_DIR) fclean
	@echo "Cleaned Minishell"

re: clean all
	@echo "Recompiled Minishell"

.PHONY: all clean fclean re
