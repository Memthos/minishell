/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_lst_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:07:53 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/17 11:35:46 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_files_lst	*files_lst_pop(t_files_lst **node)
{
	t_files_lst	*new_next;

	if (!node || !*node)
		return (NULL);
	if (!(*node)->next)
	{
		if ((*node)->data)
			free((*node)->data);
		free(*node);
		*node = NULL;
		return (NULL);
	}
	new_next = (*node)->next->next;
	if ((*node)->data)
		free((*node)->data);
	(*node)->data = (*node)->next->data;
	free((*node)->next);
	(*node)->next = new_next;
	return (*node);
}

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
