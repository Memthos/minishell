/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:05:46 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/24 03:09:25 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*lst_add(t_list **head, char *data, t_token token)
{
	t_list	*cpy;

	if (NULL == head)
		return (NULL);
	if (NULL == *head)
	{
		*head = lst_new(data, token);
		return (*head);
	}
	cpy = *head;
	while (cpy->next)
		cpy = cpy->next;
	cpy->next = lst_new(data, token);
	return (*head);
}
