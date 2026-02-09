#ifndef PARSER_H
# define PARSER_H

# include "lists.h"

typedef struct	s_lxr_params
{
	t_quote_t	quote;
	size_t		p_dpt;
	size_t		i;
}				t_lxr_params;

/**
 * @brief First step of parsing, apply a token to each part
 * of the string by separating them.
 * @param lxr A pointer to the head of the list.
 * @param s The string written as input.
 * @param ret A pointer to an integer, it will be 1 if an error occurred.
 */
void	lexer(t_lxr_lst **lxr, char *s, int *ret);

/**
 * @brief Convert the last node of t_lxr_lst if it only contains numbers.
 * @param lxr The node to check.
 */
void	set_io_number_t(t_lxr_lst *lxr);

/**
 * @brief Check if the data inside the node
 * has the right format to be an ASSIGNMENT
 * @param lxr The node to check.
 */
void	check_ASSIGNMENT(t_lxr_lst *lxr);

/**
 * @brief Return a new string of len size from input.
 * @param input The original string.
 * @param len the wanted size of the returned string.
 * @return The newly created string.
 */
char	*make_str(char *input, size_t len);

/**
 * @brief Return true if the quote state changed.
 * @param state A pointer to the quote state.
 * @param p A pointer to the lexer params.
 * @return 1 if the quote state changed else 0.
 */
int			check_quote(t_lxr_params *p, char c);

/// @brief Make the base of the AST tree, calls all the other functions
/// of the AST.
/// @param lxr A node pointing to the currently looked at token.
/// @return The newly created ast tree.
t_ast_lst	*complete_command_r(t_lxr_lst **lxr);

/// @brief Make an ast node for a simple command and consume the lexer.
/// @param lxr A node pointing to the currently looked at token.
/// @return The newly created ast node.
t_ast_lst	*simple_command_r(t_lxr_lst **lxr);

/// @brief Check if the given node can be of redirect type
/// @param lxr A pointer to the given node
int			is_io_redirect(t_lxr_lst **lxr);

/// @brief Create an a small ast tree with an io_redirect cmd.
/// @param lxr A pointer to the currently looked at lexer node.
/// @return Return a redirect_io ast tree.
t_ast_lst	*io_redirect_r(t_lxr_lst **lxr);

#endif
