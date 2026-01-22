/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:05:46 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/22 13:13:57 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/list.h"

t_list	*lst_add(t_list **head, char *data, t_token token)
{
	t_list	*cpy;

	if (NULL == head)
		return (NULL);
	if (NULL == *head)
	{
		*head = lst_new(data, token);
		return (*head);
	}
	cpy = *head;
	while (cpy->next)
		cpy = cpy->next;
	cpy->next = lst_new(data, token);
	return (*head);
}
