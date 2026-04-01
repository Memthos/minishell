CC=cc
CFLAGS=-Werror -Wall -Wextra -g

INCLUDES_DIR = includes/

VPATH = srcs:srcs/lists:srcs/commands:srcs/dictionary:srcs/parser:srcs/utils:srcs/outputs
SRCS =	minishell.c \
		init.c \
		shell.c \
		pipes.c \
		execute.c \
		sighandle.c \
		error_output.c \
		utils.c string_utils.c \
		heredoc.c \
		parser.c expand.c expand_utils.c quotes.c \
		wildcards.c wildcards_utils.c \
		ast_lst_new.c ast_lst_clear.c ast_lst_last.c ast_tools.c \
		ast_main_rules.c ast_cmp_rules.c ast_cmd_rules.c ast_cmd_utils.c \
		ast_red_rules.c \
		lexer.c lxr_checks.c lxr_post_tokenization.c lxr_lst_add.c \
		lxr_lst_append.c lxr_lst_last.c lxr_lst_new.c lxr_lst_remove.c \
		lxr_lst_size.c \
		commands.c exec.c cd.c env.c exit.c export.c echo.c pwd.c unset.c \
		dict_add.c dict_clear.c dict_get.c dict_get_data.c dict_new.c \
		dict_remove.c dict_update.c dict_size.c dict_sort.c dict_copy.c \
		dict_to_array.c dict_display.c dict_update.c dict_size.c dict_sort.c \
		dict_to_array.c dict_display.c \
		files_lst_add.c files_lst_last.c files_lst_remove.c \
		cmds_lst_add.c cmds_lst_last.c cmds_lst_remove.c \

OBJDIR = objs/
OBJECTS = $(addprefix $(OBJDIR), $(SRCS:.c=.o))
OBJECTS_BONUS = $(addprefix $(OBJDIR), $(SRCS_BONUS:.c=.o))

LIBFT_DIR = libs/libft_tools/
LIBFT = $(addprefix $(LIBFT_DIR), libft_tools.a)
LIBS = $(LIBFT) -lreadline

NAME = minishell

all: $(NAME)

bonus: $(OBJDIR).bonus

$(NAME): $(OBJECTS) | $(LIBFT)
	@$(CC) $(CFLAGS) -o $@ $^ -I$(INCLUDES_DIR) $(LIBS)
	@echo "Finished compiling Minishell"

$(OBJDIR).bonus: $(OBJECTS_BONUS) | $(LIBFT)
	@$(CC) $(CFLAGS) -o $@ $^ -I$(INCLUDES_DIR) $(LIBS)
	@touch $(OBJDIR).bonus
	@echo "Finished compiling Minishell bonuses"

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

.PHONY: all clean fclean re bonus
