CC=gcc
CFLAGS=-Werror -Wall -Wextra -g

INCLUDES_DIR = includes/

VPATH = srcs:srcs/lists:srcs/commands:srcs/dictionary:srcs/parser:srcs/utils:srcs/outputs
SRCS =	minishell.c \
		init.c \
		execute.c \
		environment.c \
		sighandle.c \
		parser.c parser_tools.c expand.c \
		ast_lst_new.c ast_lst_clear.c ast_main_rules.c ast_cmp_rules.c \
		ast_cmd_rules.c ast_red_rules.c ast_tools.c \
		lexer.c lexer_cleanup.c lxr_lst_add.c lxr_lst_append.c lxr_lst_last.c \
		lxr_lst_new.c lxr_lst_remove.c lxr_lst_size.c \
		commands.c exec.c cd.c env.c exit.c export.c echo.c pwd.c unset.c \
		dict_add.c dict_clear.c dict_get.c dict_new.c dict_remove.c \
		dict_update.c dict_size.c dict_sort.c dict_to_array.c dict_display.c \
		error_output.c \
		utils.c string_utils.c

OBJDIR = objs/
OBJECTS = $(addprefix $(OBJDIR), $(SRCS:.c=.o))

LIBFT_DIR = libs/libft_tools/
LIBFT = $(addprefix $(LIBFT_DIR), libft_tools.a)
LIBS = $(LIBFT) -lreadline

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
