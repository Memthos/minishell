/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_main_rules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:03:21 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/10 11:09:15 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast_lst	*pipe_sequence_r(t_lxr_lst **lxr)
{
	t_ast_lst	*cmd;
	t_ast_lst	*pipe;

	cmd = simple_command_r(lxr);
	while (peek(lxr, PIPE))
	{
		pipe = ast_lst_new(lxr);
		pipe->left = cmd;
		while (peek(lxr, NEW_LINE))
			consume(lxr);
		pipe->right = simple_command_r(lxr);
		cmd = pipe;
	}
	return (cmd);
}

static t_ast_lst	*and_or_r(t_lxr_lst **lxr)
{
	t_ast_lst	*cmd;
	t_ast_lst	*and_or;

	cmd = pipe_sequence_r(lxr);
	while (peek(lxr, AND_IF) || peek(lxr, OR_IF))
	{
		and_or = ast_lst_new(lxr);
		and_or->left = cmd;
		while (peek(lxr, NEW_LINE))
			consume(lxr);
		and_or->right = pipe_sequence_r(lxr);
		cmd = and_or;
	}
	return (cmd);
}

t_ast_lst	*complete_command_r(t_lxr_lst **lxr)
{
	t_ast_lst	*cmd;

	cmd = and_or_r(lxr);
	while (peek(lxr, NEW_LINE))
		consume(lxr);
	return (cmd);
}
