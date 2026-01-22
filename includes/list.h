/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:08:39 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/22 13:20:30 by juperrin         ###   ########.fr       */
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
 * @brief Returns an allocated pointer to a t_list node.
 * @param data The data to store in the node.
 * @param token The corresponding token for data.
 */
t_list	*lst_new(char *data, t_token token);

/**
 * @brief Adds a node at the end of head. Returns the new list.
 * @param head The head / start of the list.
 * @param data The data to store in the node.
 * @param token The corresponding token for data.
 */
t_list	*lst_add(t_list **head, char *data, t_token token);

#endif