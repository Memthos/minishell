/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_main_rules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:03:21 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/26 15:57:37 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast_lst	*pipe_seq_tree(t_lxr_lst **lxr, t_ast_lst **node,
	t_status *status)
{
	t_ast_lst	*pipe;

	pipe = ast_lst_new(lxr, status);
	if (*status)
		return (NULL);
	pipe->left = *node;
	while (peek(lxr, NEW_LINE))
		consume(lxr);
	pipe->right = command_r(lxr, status);
	if (*status)
		ast_lst_clear(&pipe);
	return (pipe);
}

static t_ast_lst	*pipe_sequence_r(t_lxr_lst **lxr, t_status *status)
{
	t_ast_lst	*cmd;
	t_ast_lst	*pipe;

	cmd = command_r(lxr, status);
	if (*status)
		return (NULL);
	if (!peek(lxr, PIPE))
		return (cmd);
	pipe = pipe_seq_tree(lxr, &cmd, status);
	if (*status)
		return (NULL);
	while (peek(lxr, PIPE))
	{
		cmd = pipe;
		pipe = pipe_seq_tree(lxr, &cmd, status);
	}
	if (*status)
		ast_lst_clear(&pipe);
	return (pipe);
}

static t_ast_lst	*and_or_tree(t_lxr_lst **lxr, t_ast_lst **node,
	t_status *status)
{
	t_ast_lst	*and_or;

	and_or = ast_lst_new(lxr, status);
	if (*status)
		return (NULL);
	and_or->left = *node;
	while (peek(lxr, NEW_LINE))
		consume(lxr);
	and_or->right = pipe_sequence_r(lxr, status);
	if (*status)
		ast_lst_clear(&and_or);
	return (and_or);
}

t_ast_lst	*and_or_r(t_lxr_lst **lxr, t_status *status)
{
	t_ast_lst	*and_or;
	t_ast_lst	*cmd;

	cmd = pipe_sequence_r(lxr, status);
	if (*status)
		return (NULL);
	if (!peek(lxr, AND_IF) && !peek(lxr, OR_IF))
		return (cmd);
	and_or = and_or_tree(lxr, &cmd, status);
	if (*status)
		return (NULL);
	while (!*status && (peek(lxr, AND_IF) || peek(lxr, OR_IF)))
	{
		cmd = and_or;
		and_or = and_or_tree(lxr, &cmd, status);
	}
	if (*status)
		ast_lst_clear(&and_or);
	return (and_or);
}

void	complete_command_r(t_lxr_lst **lxr, t_shell *shell, t_status *status)
{
	t_ast_lst	*ast;

	while (!*status && lxr && *lxr)
	{
		ast = and_or_r(lxr, status);
		cmds_lst_add(ast, &shell->cmd_ast);
		if (*status)
			break ;
		while (peek(lxr, NEW_LINE))
			consume(lxr);
	}
	if (*status)
		cmds_lst_clear(&shell->cmd_ast);
}
