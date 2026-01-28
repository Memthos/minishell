#ifndef PARSER_H
# define PARSER_H

# include "lists.h"

/**
 * @brief First step of parsing, apply a token to each part
 * of the string by separating them.
 * @param lst A pointer to the head of lst.
 * @param s The string written as input.
 */
void	lexer(t_lxr_lst **lst, char *s);

/**
 * @brief Convert the last node of t_lxr_lst if it only contains numbers.
 * @param lst The node to check.
 */
void	set_io_number_t(t_lxr_lst *lst);


/**
 * @brief Return a new string of len size from input.
 * @param input The original string.
 * @param len the wanted size of the returned string.
 * @return The newly created string.
 */
char	*make_str(char *input, size_t len);


/**
 * @brief Return true if the next char is a newline.
 * @param s The input string.
 * @param index A pointer to the input index.
 * @return 1 if the next char is a newline else 0.
 */
int		is_newline(char *s, size_t *index);

/**
 * @brief Return true if the next char is an operator.
 * @param s The input string.
 * @return 1 if the next char is an operator else 0.
 */
int	get_operator(char *s);

/**
 * @brief Return true if the quote state changed.
 * @param state A pointer to the quote state.
 * @param c The char to check.
 * @param index A pointer to the input index.
 * @return 1 if the quote state changed else 0.
 */
int	check_quote(t_quote_t *state, char c);

#endif
