/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 10:17:40 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/17 18:17:03 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	peek(t_lxr_lst **node, t_token token)
{
	if (!node || !(*node))
		return (0);
	if ((*node)->token == token)
		return (1);
	return (0);
}

void	consume(t_lxr_lst **node)
{
	t_lxr_lst	*consumed;

	if (!node || !*node)
		return ;
	consumed = (*node);
	*node = (*node)->next;
	if (consumed->data)
		free(consumed->data);
	free(consumed);
}
