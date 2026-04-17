/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_lst_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:07:53 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/17 11:35:46 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
