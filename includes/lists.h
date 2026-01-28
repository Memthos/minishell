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

typedef struct s_lxr_lst
{
	char				*data;
	t_token				token;
	size_t				p_dpt;
	struct s_lxr_lst	*next;
}						t_lxr_lst;

typedef struct s_ast_lst
{
	char				*data;
	t_token				token;
	size_t				p_dpt;
	struct s_ast_lst	*left;
	struct s_ast_lst	*right;
}						t_ast_lst;

/**
 * @brief Allocates memory for a new node.
 * @param data The data to store in the node. It has to be allocated !
 * @param token The corresponding token for data.
 * @param p_dpt The current parenthesis depth.
 * @return The created node.
 */
t_lxr_lst	*lxr_lst_new(char *data, t_token token, size_t p_dpt);

/**
 * @brief Adds a new node at the end of the list.
 * @param head The head / start of the list.
 * @param data The data to store in the node. It has to be allocated !
 * @param token The corresponding token for data.
 * @param p_dpt The current parenthesis depth.
 * @return The updated version of the list passed in.
 */
t_lxr_lst	*lxr_lst_add(t_lxr_lst **head, char *data, t_token t, size_t p_dpt);

/**
 * @brief Removes the last node of head.
 * @param head The head / start of the list.
 * @return The updated version of the list passed in.
 */
t_lxr_lst	*lxr_lst_remove(t_lxr_lst **head);

/**
 * @brief Clears the list passed in.
 * @param head The head / start of the list.
 */
void		lxr_lst_clear(t_lxr_lst **head);

/**
 * @brief Count the number of nodes in a list.
 * @param head The head / start of the list.
 * @return The number of nodes in the list.
 */
t_uint		lxr_lst_size(t_lxr_lst *head);

/**
 * @brief Return the last node of the list.
 * @param head The head / start of the list.
 * @return The last node of the list.
 */
t_lxr_lst	*lxr_lst_last(t_lxr_lst *head);

/**
 * @brief Append a char to the given node.
 * @param node The node to append.
 * @param c The char to append.
 * @return Nothing.
 */
void		lxr_lst_append(t_lxr_lst **node, char c, t_token token);

/**
 * @brief Allocates memory for a new node.
 * @param data The data to store in the node. It has to be allocated !
 * @param token The corresponding token for data.
 * @param p_dpt The current parenthesis depth.
 * @return The created node.
 */
t_ast_lst	*ast_lst_new(char *data, t_token token, size_t p_dpt);

/**
 * @brief Return true if the node is the same as the input token.
 * @param node A pointer to the current node of the list.
 * @param token The searched token.
 * @return Return 1 if the condition is true.
 */
int			peek(t_lxr_lst **node, t_token token);

/**
 * @brief Return the first node and set the pointer of lst to the next node.
 * @param node A pointer to the current node of the list.
 * @return The consumed node.
 */
t_lxr_lst	*consume(t_lxr_lst **node);

#endif
