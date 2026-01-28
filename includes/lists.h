/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:08:39 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/28 22:27:56 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H

# include "definitions.h"
# include "enums.h"

typedef struct s_list
{
	char			*data;
	t_token			token;
	size_t			parenth_dpt;
	struct s_list	*next;
}	t_list;

typedef struct s_ast
{
	char	*str;
	t_token	token;
	size_t	parenth_dpt;
	struct s_ast left;
	struct s_ast right;
}	t_ast;

/**
 * @brief Allocates memory for a new node.
 * @param data The data to store in the node. It has to be allocated !
 * @param token The corresponding token for data.
 * @param parenth_dpt The current parenthesis depth.
 * @return The created node.
 */
t_list	*lst_new(char *data, t_token token, size_t parenth_dpt);

/**
 * @brief Adds a new node at the end of the list.
 * @param head The head / start of the list.
 * @param data The data to store in the node. It has to be allocated !
 * @param token The corresponding token for data.
 * @param parenth_dpt The current parenthesis depth.
 * @return The updated version of the list passed in.
 */
t_list	*lst_add(t_list **head, char *data, t_token token, size_t parenth_dpt);

/**
 * @brief Removes the last node of head.
 * @param head The head / start of the list.
 * @return The updated version of the list passed in.
 */
t_list	*lst_remove(t_list **head);

/**
 * @brief Clears the list passed in.
 * @param head The head / start of the list.
 */
void	lst_clear(t_list **head);

/**
 * @brief Count the number of nodes in a list.
 * @param head The head / start of the list.
 * @return The number of nodes in the list.
 */
t_uint	lst_size(t_list *head);

/**
 * @brief Return the last node of the list.
 * @param head The head / start of the list.
 * @return The last node of the list.
 */
t_list	*lst_last(t_list *head);

/**
 * @brief Append a char to the given node.
 * @param node The node to append.
 * @param c The char to append.
 * @return Nothing.
 */
void	lst_append(t_list **node, char c, t_token token);

/**
 * @brief Return true if the node is the same as the input token.
 * @param node A pointer to the current node of the list.
 * @param token The searched token.
 * @return Return 1 if the condition is true.
 */
int		peek(t_list **node, t_token token);

/**
 * @brief Return the first node and set the pointer of lst to the next node.
 * @param node A pointer to the current node of the list.
 * @return The consumed node.
 */
t_list	*consume(t_list **node);

#endif
