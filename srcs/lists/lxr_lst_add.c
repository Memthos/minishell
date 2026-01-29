/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lxr_lst_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:05:46 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/28 23:08:55 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lxr_lst	*lxr_lst_add(t_lxr_lst **head, char *data, t_token t, size_t p_dpt)
{
	t_lxr_lst	*tmp;

	if (NULL == head)
		return (NULL);
	if (NULL == *head)
	{
		*head = lxr_lst_new(data, t, p_dpt);
		return (*head);
	}
	tmp = lxr_lst_last(*head);
	if (!tmp->data && tmp->token == TOKEN)
	{
		tmp->data = data;
		tmp->token = t;
		tmp->p_dpt = p_dpt;
	}
	else
	{
		tmp->next = lxr_lst_new(data, t, p_dpt);
		set_io_number_t(tmp);
		check_assignment_w(tmp);
	}
	return (*head);
}
