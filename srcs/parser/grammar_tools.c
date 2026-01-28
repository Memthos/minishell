/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 10:17:40 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/28 22:32:05 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	peek(t_list **node, t_token token)
{
	if ((*node)->token == token)
		return (1);
	return (0);
}

t_list	*consume(t_list **node)
{
	t_list	*consumed;

	consumed = (*node);
	(*node) = (*node)->next;
	return (consumed);
}
