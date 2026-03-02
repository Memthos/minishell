/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_lst_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:08:02 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/02 12:52:06 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_lst	*ast_lst_last(t_ast_lst *head, t_side side)
{
	if (!head)
		return (NULL);
	if (side == LEFT)
	{
		while (head->left)
			head = head->left;
	}
	else
	{
		while (head->right)
			head = head->right;
	}
	return (head);
}
