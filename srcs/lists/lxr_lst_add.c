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

int	lxr_lst_add(t_lxr_lst **head, char *data, t_token t, t_lxr_p *p)
{
	t_lxr_lst	*tmp;

	if (NULL == head)
		return (1);
	if (NULL == *head)
	{
		*head = lxr_lst_new(data, t, p->p_dpt, p->quote);
		if (!*head)
			return (1);
		return (0);
	}
	tmp = lxr_lst_last(*head);
	if (!tmp->data && tmp->token == TOKEN)
		*tmp = (t_lxr_lst){.data = data, .token = t,
			.p_dpt = p->p_dpt, p->quote};
	else
	{
		tmp->next = lxr_lst_new(data, t, p->p_dpt, p->quote);
		if (!tmp->next)
			return (1);
		set_io_number_t(tmp);
		check_ASSIGNMENT_W(tmp);
	}
	return (0);
}
