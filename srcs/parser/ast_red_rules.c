/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_red_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:09:08 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/02 13:03:16 by mperrine         ###   ########.fr       */
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

t_ast_lst	*io_redirect_r(t_lxr_lst **lxr, int *ret, t_side side)
{
	t_ast_lst	*cmd;
	t_ast_lst	*red;

	cmd = NULL;
	if (peek(lxr, IO_NUMBER))
		cmd = ast_lst_new(lxr, ret, 0);
	if (*ret && is_io_redirect(lxr) == 2)
		red = ast_lst_new(lxr, ret, 0);
	else
		*ret = 0;
	if (*ret && peek(lxr, WORD) && side == LEFT)
		red->left = ast_lst_new(lxr, ret, 0);
	else if (*ret && peek(lxr, WORD) && side == RIGHT)
		red->right = ast_lst_new(lxr, ret, 0);
	else
		*ret = 0;
	if (cmd && side == LEFT)
		cmd->left = red;
	else if (cmd && side == RIGHT)
		cmd->right = red;
	else
		cmd = red;
	if (!*ret)
		ast_lst_clear(&cmd);
	return (cmd);
}
