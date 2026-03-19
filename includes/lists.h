/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:06:20 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/19 19:04:33 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H

# include "definitions.h"
# include <stdlib.h>

typedef struct s_lxr_lst
{
	char				*data;
	t_token				token;
	long				p_dpt;
	struct s_lxr_lst	*next;
}						t_lxr_lst;

typedef struct s_ast_lst
{
	char				*data;
	t_token				token;
	int					expand_state;
	struct s_ast_lst	*left;
	struct s_ast_lst	*right;
}						t_ast_lst;

typedef struct s_files_lst
{
	char				*data;
	struct s_files_lst	*next;
}						t_files_lst;

/**
 * @brief Allocates memory for a new node.
 * @param data The data to store in the node. It has to be allocated !
 * @param token The corresponding token for data.
 * @param p_dpt The current parenthesis depth.
 * @return The created node.
 */
t_lxr_lst	*lxr_lst_new(char *data, t_token token, long p_dpt);

/**
 * @brief Adds a new node at the end of the list.
 * @param head The head / start of the list.
 * @param data The data to store in the node. It has to be allocated !
 * @param token The corresponding token for data.
 * @param p_dpt The current parenthesis depth.
 * @return The exit status of the function.
 */
t_status	lxr_lst_add(t_lxr_lst **head, char *data, t_token t, long p_dpt);

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
 * @return The exit status of the function.
 */
t_status	lxr_lst_append(t_lxr_lst **node, char c);

/**
 * @brief Allocates memory for a new node.
 * @param lxr The lexer node to use.
 * @param status The status of the parser.
 * @return The created node.
 */
t_ast_lst	*ast_lst_new(t_lxr_lst **lxr, t_status *status);

/// @brief Allocates memory for a new node.
/// @param data The data of the new node.
/// @param token The token of the new node.
/// @param status The status of the parser.
/// @return The created node.
t_ast_lst	*ast_lst_new_char(char *data, t_token token, t_status *status);

/// @brief Clear the ast.
/// @param head A pointer to the first node of the ast.
void		ast_lst_clear(t_ast_lst **head);

/// @brief Returns the last node of the list.
/// @param head The head / start of the list.
/// @param side The side of the list to check.
/// @return The last node of the list.
t_ast_lst	*ast_lst_last(t_ast_lst *head, t_side side);

/**
 * @brief Return true if the node is the same as the input token.
 * @param node A pointer to the current node of the list.
 * @param token The searched token.
 * @return Return 1 if the condition is true.
 */
int			peek(t_lxr_lst **node, t_token token);

/**
 * @brief Set the pointer of node to the next node and free the consumed one.
 * @param node A pointer to the current node of the lexer.
 */
void		consume(t_lxr_lst **node);

/**
 * @brief Counts the number of commands in ast.
 */
t_uint		ast_cmd_count(t_ast_lst *ast);

/**
 * @brief Counts the number of arguments for the contained command in ast.
 * @return The number of arguments plus the command.
 */
t_uint		ast_cmd_size(t_ast_lst *ast);

/**
 * @brief Counts the number of pipes in ast.
 * @return The number if pipes in ast.
 */
t_uint		ast_pipe_count(t_ast_lst *ast);

/// @brief Return the last node of the list.
/// @param head The head / start of the list.
/// @return The last node of the list.
t_files_lst	*file_lst_last(t_files_lst *head);

/// @brief Adds a new node at the end of the list.
/// @param s The data to store in the node.
/// @param files The head / start of the list.
/// @param status The status of the parser.
/// @return 0 if the function is successful, else it returns 1.
int			files_lst_add(char *s, t_files_lst **files, t_status *status);

/// @brief Removes the last node of head.
/// @param head The head / start of the list.
/// @return The updated version of the list passed in.
t_files_lst	*files_lst_remove(t_files_lst **head);

/// @brief Clears the list passed in.
/// @param head The head / start of the list.
void		files_lst_clear(t_files_lst **head);

/// @brief Pop the given node from the list.
/// @param node The node to pop.
/// @return The node or NULL if it was freed.
t_files_lst	*files_lst_pop(t_files_lst **node);

#endif
