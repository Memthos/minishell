/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:08:39 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/22 13:40:46 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stdlib.h>
# include "token.h"

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

#endif