VPATH=srcs:srcs/lists:srcs/commands:srcs/parser:srcs/utils
OBJDIR=objs/
INCLUDES_DIR=includes/

SRCS=minishell.c \
		init.c \
		sighandle.c \
		utils.c \
		parser.c \
		ast_lst_new.c ast_lst_clear.c ast_main_rules.c ast_cmp_rules.c \
		ast_cmd_rules.c ast_red_rules.c ast_tools.c \
		lexer.c lexer_tools.c lxr_lst_add.c lxr_lst_append.c \
		lxr_lst_last.c lxr_lst_new.c lxr_lst_remove.c lxr_lst_size.c


OBJECTS=$(addprefix $(OBJDIR), $(SRCS:.c=.o))

LIBFT_DIR=libs/libft_tools/
LIBFT=$(addprefix $(LIBFT_DIR), libft_tools.a)

LIBS=$(LIBFT) -lreadline

CC=gcc
CFLAGS=-Werror -Wall -Wextra -g

NAME=minishell

all: $(NAME)

$(NAME): $(OBJECTS) | $(LIBFT)
	@$(CC) $(CFLAGS) -o $@ $^ -I$(INCLUDES_DIR) $(LIBS)
	@echo "Finished compiling Minishell"

$(OBJDIR)%.o: %.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(LIBFT):
	@make -sC $(LIBFT_DIR) all
	@echo "Compiled library Libft"

$(OBJDIR):
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
