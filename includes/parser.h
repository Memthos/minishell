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
 * @param input The original string
 * @param len the wanted size of the returned string
 * @return The newly created string
 */
char	*make_str(char *input, size_t len);


/**
 * @brief Return true if the next char is a newline
 * @param s THe input string
 * @param index A pointer to the input index
 * @return 1 if the next char is a newline else 0
 */
int		is_newline(char *s, size_t *index);

#endif
