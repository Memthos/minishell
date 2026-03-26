/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_lst_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:06:02 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/26 13:21:03 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	cmds_lst_add(t_ast_lst *ast, t_cmd_lst **cmds)
{
	t_cmd_lst	*node;

	node = malloc(sizeof(t_cmd_lst));
	if (!node)
		return (ALLOCATION_FAILURE);
	node->ast = ast;
	node->next = NULL;
	if (!cmds || !*cmds)
		*cmds = node;
	else
		cmds_lst_last(*cmds)->next = node;
	return (SUCCESS);
}
