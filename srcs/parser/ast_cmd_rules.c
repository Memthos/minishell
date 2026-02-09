/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:12:47 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/09 13:57:08 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast_lst	*cmd_suffix_r(t_lxr_lst **lxr)
{
	t_ast_lst	*cmd;
	t_ast_lst	*suffix;

	cmd = NULL;
	if (is_io_redirect(lxr))
		cmd = io_redirect_r(lxr);
	else if (peek(lxr, WORD))
		cmd = ast_lst_new(lxr);
	while (is_io_redirect (lxr) || peek(lxr, WORD))
	{
		if (is_io_redirect(lxr))
			suffix = io_redirect_r(lxr);
		else
			suffix = ast_lst_new(lxr);
		suffix->left = cmd;
		cmd = suffix;
	}
	return (cmd);
}

static t_ast_lst	*cmd_word_r(t_lxr_lst **lxr)
{
	t_ast_lst	*node;

	node = NULL;
	if (peek(lxr, WORD) || peek(lxr, ASSIGNMENT))
		ast_lst_new(lxr);
	return (node);
}

static t_ast_lst	*cmd_prefix_r(t_lxr_lst **lxr)
{
	t_ast_lst	*cmd;
	t_ast_lst	*prefix;

	cmd = NULL;
	if (is_io_redirect(lxr))
		cmd = io_redirect_r(lxr);
	else if (peek(lxr, ASSIGNMENT))
		cmd = ast_lst_new(lxr);
	while (is_io_redirect (lxr) || peek(lxr, ASSIGNMENT))
	{
		if (is_io_redirect(lxr))
			prefix = io_redirect_r(lxr);
		else
			prefix = ast_lst_new(lxr);
		prefix->left = cmd;
		cmd = prefix;
	}
	return (cmd);
}

t_ast_lst	*simple_command_r(t_lxr_lst **lxr)
{
	t_ast_lst	*simple_cmd;
	t_ast_lst	*cmd;

	cmd = cmd_prefix_r(lxr);
	simple_cmd = cmd_word_r(lxr);
	if (!simple_cmd && !cmd)
		return (NULL);
	if (!simple_cmd)
		return (cmd);
	else
		simple_cmd->left = cmd;
	simple_cmd->right = cmd_suffix_r(lxr);
	return (simple_cmd);
}
