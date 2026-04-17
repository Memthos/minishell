/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_lst_last.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:08:02 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/17 22:17:24 by memthos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_char_lst	*file_lst_last(t_char_lst *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}
