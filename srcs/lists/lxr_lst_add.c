/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lxr_lst_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:43:38 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/25 21:00:19 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	lxr_lst_add(t_lxr_lst **head, char *data, t_token t, long p_dpt)
{
	t_lxr_lst	*tmp;

	if (!data && t != TOKEN && t != NEW_LINE)
		return (ALLOCATION_FAILURE);
	if (NULL == head)
		return (FAILURE);
	if (NULL == *head)
	{
		*head = lxr_lst_new(data, t, p_dpt);
		if (!*head)
			return (ALLOCATION_FAILURE);
		return (SUCCESS);
	}
	tmp = lxr_lst_last(*head);
	if (!tmp->data && tmp->token == TOKEN)
		*tmp = (t_lxr_lst){.data = data, .token = t, .p_dpt = p_dpt};
	else
	{
		tmp->next = lxr_lst_new(data, t, p_dpt);
		if (!tmp->next)
			return (ALLOCATION_FAILURE);
	}
	return (SUCCESS);
}
