/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lxr_lst_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:08:02 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/11 12:57:03 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lxr_lst	*lxr_lst_last(t_lxr_lst *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}
