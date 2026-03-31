/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_lst_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:06:02 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/30 16:09:25 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_status	heredoc_lst_add(t_ast_lst *ast, t_hd_lst **lst)
{
	t_hd_lst	*node;

	node = malloc(sizeof(t_hd_lst));
	if (!node)
		return (ALLOCATION_FAILURE);
	node->node = ast;
	node->next = NULL;
	if (!lst || !*lst)
		*lst = node;
	else
		heredoc_lst_last(*lst)->next = node;
	return (SUCCESS);
}
