/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_red_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:09:08 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/25 13:30:02 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_io_redirect(t_lxr_lst **lxr)
{
	if (peek(lxr, IO_NUMBER))
		return (1);
	else if (peek(lxr, LESS))
		return (2);
	else if (peek(lxr, GREAT))
		return (2);
	else if (peek(lxr, DGREAT))
		return (2);
	else if (peek(lxr, DLESS))
		return (2);
	else
		return (0);
}

t_ast_lst	*io_redirect_r(t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*cmd;
	t_ast_lst	*tail;

	if (peek(lxr, IO_NUMBER))
	{
		cmd = ast_lst_new(lxr, ret, 0);
		if (!*ret)
			return (NULL);
	}
	tail = cmd;
	if (is_io_redirect(lxr) == 2)
		tail->left = ast_lst_new(lxr, ret, 0);
	else
		*ret = 0;
	if (*ret && peek(lxr, WORD))
	{
		tail = tail->left;
		tail->left = ast_lst_new(lxr, ret, 0);
	}
	if (!*ret)
		ast_lst_clear(&cmd);
	return (cmd);
}
