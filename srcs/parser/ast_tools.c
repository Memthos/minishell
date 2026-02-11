/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 10:17:40 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/11 09:37:05 by mperrine         ###   ########.fr       */
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

	consumed = (*node);
	*node = (*node)->next;
	free(consumed->data);
	free(consumed);
}
