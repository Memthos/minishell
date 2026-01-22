/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:08:39 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/22 14:13:03 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stdlib.h>
# include "enums.h"

typedef struct s_list
{
	char			*data;
	t_token			token;
	struct s_list	*next;
}	t_list;

/**
 * @brief Allocates memory for a new node.
 * @param data The data to store in the node.
 * @param token The corresponding token for data.
 * @return The created node.
 */
t_list	*lst_new(char *data, t_token token);

/**
 * @brief Adds a new node at the end of the list.
 * @param head The head / start of the list.
 * @param data The data to store in the node.
 * @param token The corresponding token for data.
 * @return The updated version of the list passed in.
 */
t_list	*lst_add(t_list **head, char *data, t_token token);

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

#endif