/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_lst_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:07:53 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/17 12:58:49 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_files_lst	*files_lst_remove(t_files_lst **head)
{
	t_files_lst	*cpy;

	if (!head || !*head)
		return (NULL);
	if (!(*head)->next)
	{
		if ((*head)->data)
			free((*head)->data);
		free(*head);
		*head = NULL;
		return (NULL);
	}
	cpy = *head;
	while (cpy->next->next)
		cpy = cpy->next;
	if (cpy->next->data)
		free(cpy->next->data);
	free(cpy->next);
	cpy->next = NULL;
	return (*head);
}

void	files_lst_clear(t_files_lst **head)
{
	if (NULL == head || NULL == *head)
		return ;
	while (*head)
		files_lst_remove(head);
	*head = NULL;
	return ;
}
