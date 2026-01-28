/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lxr_lst_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:26:13 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/28 23:09:44 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lxr_lst	*lxr_lst_remove(t_lxr_lst **head)
{
	t_lxr_lst	*cpy;

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

void	lxr_lst_clear(t_lxr_lst **head)
{
	if (NULL == head || NULL == *head)
		return ;
	while (*head)
		lxr_lst_remove(head);
	return ;
}
