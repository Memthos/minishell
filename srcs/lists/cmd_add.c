/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:05:46 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/27 18:13:06 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*cmd_add(t_cmd **head, char *data, t_token token)
{
	if (NULL == head)
		return (NULL);
	if (NULL == *head)
	{
		*head = cmd_new(data, token);
		return (*head);
	}
	else
		cmd_last(*head)->next = cmd_new(data, token);
	return (*head);
}
