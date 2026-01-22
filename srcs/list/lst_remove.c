/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:26:13 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/22 13:32:11 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/list.h"

t_list	*lst_remove(t_list **head)
{
	t_list	*cpy;

	if (NULL == head || NULL == *head)
		return (NULL);
	if (NULL == (*head)->next)
	{
		free((*head)->data);
		free(*head);
		*head = NULL;
		return (NULL);
	}
	cpy = *head;
	while (cpy->next->next)
		cpy = cpy->next;
	free(cpy->next->data);
	free(cpy->next);
	cpy->next = NULL;
	return (*head);
}
