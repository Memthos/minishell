/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_red_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:09:08 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/13 15:36:03 by mperrine         ###   ########.fr       */
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

t_ast_lst	*io_redirect_r(t_lxr_lst **lxr)
{
	t_ast_lst	*cmd;
	t_ast_lst	*tail;
	int			ret;

	ret = 0;
	if (peek(lxr, IO_NUMBER))
	{
		cmd = ast_lst_new(lxr);
		if (!cmd)
			return (NULL);
	}
	tail = cmd;
	if (is_io_redirect(lxr) == 2)
		tail->left = ast_lst_new(lxr);
	if (!tail->left)
		ret = 1;
	else
		tail = tail->left;
	if (!ret && peek(lxr, WORD))
		tail->left = ast_lst_new(lxr);
	if (ret == 1 || !tail->left)
		ast_lst_clear(&cmd);
	if (ret == 1 || !tail->left)
		return (NULL);
	return (cmd);
}
