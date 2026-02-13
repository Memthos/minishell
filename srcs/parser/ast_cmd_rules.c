/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:12:47 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/13 15:55:06 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast_lst	*cmd_suffix_r(t_lxr_lst **lxr)
{
	t_ast_lst	*cmd;
	t_ast_lst	*suffix;
	t_ast_lst	*tail;

	if (is_io_redirect(lxr))
		cmd = io_redirect_r(lxr);
	else if (peek(lxr, WORD))
		cmd = ast_lst_new(lxr);
	if (!cmd)
		return (NULL);
	tail = cmd;
	while (is_io_redirect (lxr) || peek(lxr, WORD))
	{
		if (is_io_redirect(lxr))
			suffix = io_redirect_r(lxr);
		else
			suffix = ast_lst_new(lxr);
		if (!suffix)
			ast_lst_clear(cmd);
		if (!suffix)
			return (NULL);
		tail->left = suffix;
		tail = suffix;
	}
	return (cmd);
}

static t_ast_lst	*cmd_word_r(t_lxr_lst **lxr)
{
	t_ast_lst	*node;

	if (peek(lxr, WORD) || peek(lxr, ASSIGNMENT_W))
		node = ast_lst_new(lxr);
	return (node);
}

static t_ast_lst	*cmd_prefix_r(t_lxr_lst **lxr)
{
	t_ast_lst	*cmd;
	t_ast_lst	*prefix;
	t_ast_lst	*tail;

	if (is_io_redirect(lxr))
		cmd = io_redirect_r(lxr);
	else if (peek(lxr, ASSIGNMENT_W))
		cmd = ast_lst_new(lxr);
	if (!cmd)
		return (NULL);
	tail = cmd;
	while (is_io_redirect (lxr) || peek(lxr, ASSIGNMENT_W))
	{
		if (is_io_redirect(lxr))
			prefix = io_redirect_r(lxr);
		else
			prefix = ast_lst_new(lxr);
		if (!prefix)
			ast_lst_clear(cmd);
		if (!prefix)
			return (NULL);
		tail->left = prefix;
		tail = prefix;
	}
	return (cmd);
}

t_ast_lst	*simple_command_r(t_lxr_lst **lxr)
{
	t_ast_lst	*cmd;
	t_ast_lst	*prefix;

	prefix = cmd_prefix_r(lxr);
	cmd = cmd_word_r(lxr);
	if (!cmd && !prefix)
		return (NULL);
	else if (!cmd)
		return (prefix);
	else
		cmd->left = prefix;
	cmd->right = cmd_suffix_r(lxr);
	return (cmd);
}
