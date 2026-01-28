/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:05:46 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/28 11:05:29 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*lst_add(t_list **head, char *data, t_token token, size_t parenth_dpt)
{
	t_list	*tmp;

	if (NULL == head)
		return (NULL);
	if (NULL == *head)
	{
		*head = lst_new(data, token, parenth_dpt);
		return (*head);
	}
	tmp = lst_last(*head);
	if (!tmp->data && tmp->token == TOKEN)
	{
		tmp->data = data;
		tmp->token = token;
		tmp->parenth_dpt = parenth_dpt;
	}
	else
		tmp->next = lst_new(data, token, parenth_dpt);
	set_io_number_t(tmp);
	return (*head);
}
