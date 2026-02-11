/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lxr_lst_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:07:43 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/11 10:07:44 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_uint	lxr_lst_size(t_lxr_lst *head)
{
	t_uint	size;

	size = 0;
	while (head)
	{
		++size;
		head = head->next;
	}
	return (size);
}
