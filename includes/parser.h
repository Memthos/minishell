#ifndef PARSER_H
# define PARSER_H

# include "list.h"

/**
 * @brief First step of parsing, apply a token to each part
 * of the string by separating them.
 * @param lst A pointer to the head of lst.
 * @param s The string written as input.
 * @return The list with separated args identified by tokens.
 */
void	lexer(t_list **lst, char *s);

/**
 * @brief Convert the last node of t_list if it only contains numbers.
 * @param lst The node to check.
 */
void	set_io_number_t(t_list *lst);


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

/**
 * @brief Return true if the node is the same as the input token.
 * @param lst, A pointer to the lexer list.
 * @param token The searched token.
 * @return Return 1 if the condition is true.
 */
int		peek(t_list **lst, t_token token);

/**
 * @brief Return the first node and set the pointer of lst to the next node.
 * @param lst THe pointer to the list.
 * @return The consumed node.
 */
t_list	*consume(t_list **lst);

#endif
