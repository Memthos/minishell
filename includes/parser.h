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

#endif
