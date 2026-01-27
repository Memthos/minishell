/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:46:53 by juperrin          #+#    #+#             */
/*   Updated: 2026/01/27 18:12:01 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*cmd_last(t_cmd *head)
{
	if (!head)
		return (NULL);
	while (&head->nexts[0])
		head = head->nexts;
	return (head);
}
