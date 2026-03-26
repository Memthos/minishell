/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_lst_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:07:53 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/26 14:05:40 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd_lst	*cmds_lst_remove(t_cmd_lst **head)
{
	t_cmd_lst	*cpy;

	if (!head || !*head)
		return (NULL);
	if (!(*head)->next)
	{
		if ((*head)->ast)
			ast_lst_clear(&(*head)->ast);
		free(*head);
		*head = NULL;
		return (NULL);
	}
	cpy = *head;
	while (cpy->next->next)
		cpy = cpy->next;
	if (cpy->next->ast)
		ast_lst_clear(&(*head)->ast);
	free(cpy->next);
	cpy->next = NULL;
	return (*head);
}

void	cmds_lst_clear(t_cmd_lst **head)
{
	if (NULL == head || NULL == *head)
		return ;
	while (*head)
		cmds_lst_remove(head);
	return ;
}
