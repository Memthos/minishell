/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmp_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 17:10:27 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/17 13:42:33 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_lst	*compound_cmd_r(t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*cmd;
	t_ast_lst	*term;
	t_ast_lst	*tail;

	term = and_or_r(lxr, ret);
	if (!*ret)
		return (NULL);
	tail = term;
	while (!peek(lxr, R_PAREN))
	{
		while (peek(lxr, NEW_LINE))
			consume(lxr);
		cmd = and_or_r(lxr, ret);
		if (!*ret)
			break ;
		tail->left = cmd;
		tail = cmd;
		while (peek(lxr, NEW_LINE))
			consume(lxr);
	}
	if (!*ret)
		ast_lst_clear(&term);
	return (term);
}

t_ast_lst	*redirect_loop(t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*red;
	t_ast_lst	*tail;

	while (is_io_redirect(lxr))
	{
		red = io_redirect_r(lxr, ret);
		if (!*ret)
			break ;
		tail->left = red;
		tail = red;
	}
	if (!*ret)
		ast_lst_clear(&red);
	return (red);
}
