/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_main_rules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:03:21 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/25 16:32:09 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast_lst	*pipe_seq_tree(t_lxr_lst **lxr, t_ast_lst **node, int *ret)
{
	t_ast_lst	*pipe;

	pipe = ast_lst_new(lxr, ret, 0);
	if (!*ret)
		return (NULL);
	pipe->left = *node;
	while (peek(lxr, NEW_LINE))
		consume(lxr);
	pipe->right = command_r(lxr, ret);
	if (!*ret)
		ast_lst_clear(&pipe);
	return (pipe);
}

static t_ast_lst	*pipe_sequence_r(t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*cmd;
	t_ast_lst	*pipe;

	cmd = command_r(lxr, ret);
	if (!*ret)
		return (NULL);
	if (!peek(lxr, PIPE))
		return (cmd);
	pipe = pipe_seq_tree(lxr, &cmd, ret);
	if (!*ret)
		return (NULL);
	while (peek(lxr, PIPE))
	{
		cmd = pipe;
		pipe = pipe_seq_tree(lxr, &cmd, ret);
	}
	if (!*ret)
		ast_lst_clear(&pipe);
	return (pipe);
}

static t_ast_lst	*and_or_tree(t_lxr_lst **lxr, t_ast_lst **node, int *ret)
{
	t_ast_lst	*and_or;

	and_or = ast_lst_new(lxr, ret, 0);
	if (!*ret)
		return (NULL);
	and_or->left = *node;
	while (peek(lxr, NEW_LINE))
		consume(lxr);
	and_or->right = pipe_sequence_r(lxr, ret);
	if (!*ret)
		ast_lst_clear(&and_or);
	return (and_or);
}

t_ast_lst	*and_or_r(t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*and_or;
	t_ast_lst	*cmd;

	cmd = pipe_sequence_r(lxr, ret);
	if (!*ret)
		return (NULL);
	if (!peek(lxr, AND_IF) && !peek(lxr, OR_IF))
		return (cmd);
	and_or = and_or_tree(lxr, &cmd, ret);
	if (!*ret)
		return (NULL);
	while (*ret && (peek(lxr, AND_IF) || peek(lxr, OR_IF)))
	{
		cmd = and_or;
		and_or = and_or_tree(lxr, &cmd, ret);
	}
	if (!*ret)
		ast_lst_clear(&and_or);
	return (and_or);
}

t_ast_lst	*complete_command_r(t_lxr_lst **lxr)
{
	t_ast_lst	*cmd;
	int			ret;

	ret = 1;
	cmd = and_or_r(lxr, &ret);
	if (!ret)
		return (NULL);
	while (peek(lxr, NEW_LINE))
		consume(lxr);
	return (cmd);
}
