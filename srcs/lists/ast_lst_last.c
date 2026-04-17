/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_lst_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:08:02 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/17 11:35:46 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
