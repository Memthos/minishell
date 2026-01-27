/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:05:46 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/27 16:01:27 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*cmd_add(t_cmd **head, char *data, t_token token)
{
	t_list	*tmp;

	if (NULL == head)
		return (NULL);
	if (NULL == *head)
	{
		*head = cmd_new(data, token);
		return (*head);
	}
	tmp = cmd_last(*head);
	if (!tmp->data && tmp->token == TOKEN)
	{
		tmp->data = data;
		tmp->token = token;
	}
	else
		tmp->next = cmd_new(data, token);
	return (*head);
}
