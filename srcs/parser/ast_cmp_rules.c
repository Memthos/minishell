/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmp_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 17:10:27 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/13 10:39:54 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_lst	*compound_cmd_r(t_lxr_lst **lxr)
{
	t_ast_lst	*cmd;
	t_ast_lst	*term;
	t_ast_lst	*tail;

	term = and_or_r(lxr);
	tail = term;
	while (!peek(lxr, R_PAREN))
	{
		while (peek(lxr, NEW_LINE))
			consume(lxr);
		cmd = and_or_r(lxr);
		tail->left = cmd;
		tail = cmd;
		while (peek(lxr, NEW_LINE))
			consume(lxr);
	}
	return (term);
}
