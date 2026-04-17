/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmp_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 17:10:27 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/17 11:35:46 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_lst	*compound_cmd_r(t_lxr_lst **lxr, t_status *status)
{
	t_ast_lst	*term;
	t_ast_lst	*tail;

	term = and_or_r(lxr, status);
	if (*status)
		return (NULL);
	tail = term;
	while (!peek(lxr, R_PAREN))
	{
		while (peek(lxr, NEW_LINE))
			consume(lxr);
		tail->left = and_or_r(lxr, status);
		if (*status)
			break ;
		tail = tail->left;
		while (peek(lxr, NEW_LINE))
			consume(lxr);
	}
	if (*status)
		ast_lst_clear(&term);
	consume(lxr);
	return (term);
}

t_ast_lst	*redirect_loop(t_lxr_lst **lxr, t_status *status)
{
	t_ast_lst	*red;

	if (is_io_redirect(lxr))
		red = io_redirect_r(lxr, status, LEFT);
	else
		return (NULL);
	while (!*status && is_io_redirect (lxr))
		ast_lst_last(red, LEFT)->left = io_redirect_r(lxr, status, LEFT);
	if (*status)
		ast_lst_clear(&red);
	return (red);
}
