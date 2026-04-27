/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_lst_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:07:53 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/27 16:29:11 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmds_lst_clear(t_cmd_lst **head)
{
	t_cmd_lst	*tmp;

	if (NULL == head || NULL == *head)
		return ;
	while (*head)
	{
		tmp = (*head)->next;
		ast_lst_clear(&(*head)->ast);
		free(*head);
		*head = tmp;
	}
	*head = NULL;
	return ;
}
