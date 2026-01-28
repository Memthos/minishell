/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 10:17:40 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/28 10:27:14 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	peek(t_list **lst, t_token token)
{
	if ((*lst)->token == token)
		return (1);
	return (0);
}

t_list	*consume(t_list **lst)
{
	t_list	*consumed;

	consumed = (*lst);
	(*lst) = (*lst)->next;
	return (consumed);
}
