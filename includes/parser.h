#ifndef PARSER_H
# define PARSER_H

# include "lists.h"

/**
 * @brief First step of parsing, apply a token to each part
 * of the string by separating them.
 * @param lxr A pointer to the head of the list.
 * @param s The string written as input.
 */
void	lexer(t_lxr_lst **lxr, char *s);

/**
 * @brief Convert the last node of t_lxr_lst if it only contains numbers.
 * @param lxr The node to check.
 */
void	set_io_number_t(t_lxr_lst *lxr);

/**
 * @brief Check if the data inside the node
 * has the right format to be an ASSIGNMENT_W
 * @param lxr The node to check.
 */
void	check_assignment_w(t_lxr_lst *lxr);

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
 * @param c The char to check.
 * @param index A pointer to the input index.
 * @return 1 if the quote state changed else 0.
 */
int	check_quote(t_quote_t *state, char c);

#endif
