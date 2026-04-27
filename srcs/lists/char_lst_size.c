/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_lst_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 09:23:11 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/27 09:24:01 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_uint	char_lst_size(t_char_lst *head)
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
