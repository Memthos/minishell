/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:12:47 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/23 14:05:32 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast_lst	*cmd_suffix_r(t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*cmd;
	t_ast_lst	*suffix;
	t_ast_lst	*tail;

	if (is_io_redirect(lxr))
		cmd = io_redirect_r(lxr, ret);
	else if (peek(lxr, WORD))
		cmd = ast_lst_new(lxr, ret);
	else
		return (NULL);
	tail = cmd;
	while (*ret && (is_io_redirect (lxr) || peek(lxr, WORD)))
	{
		if (is_io_redirect(lxr))
			suffix = io_redirect_r(lxr, ret);
		else
			suffix = ast_lst_new(lxr, ret);
		if (!*ret)
			break ;
		tail->left = suffix;
		tail = suffix;
	}
	if (!*ret)
		ast_lst_clear(&cmd);
	return (cmd);
}

static t_ast_lst	*cmd_word_r(t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*cmd;

	cmd = NULL;
	if (peek(lxr, WORD) || peek(lxr, ASSIGNMENT_W))
		cmd = ast_lst_new(lxr, ret);
	if (!*ret)
		ast_lst_clear(&cmd);
	return (cmd);
}

static t_ast_lst	*cmd_prefix_r(t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*cmd;
	t_ast_lst	*prefix;
	t_ast_lst	*tail;

	if (is_io_redirect(lxr))
		cmd = io_redirect_r(lxr, ret);
	else if (peek(lxr, ASSIGNMENT_W))
		cmd = ast_lst_new(lxr, ret);
	else
		return (NULL);
	tail = cmd;
	while (*ret && (is_io_redirect (lxr) || peek(lxr, ASSIGNMENT_W)))
	{
		if (is_io_redirect(lxr))
			prefix = io_redirect_r(lxr, ret);
		else
			prefix = ast_lst_new(lxr, ret);
		if (!*ret)
			break ;
		tail->left = prefix;
		tail = prefix;
	}
	if (!*ret)
		ast_lst_clear(&cmd);
	return (cmd);
}

t_ast_lst	*simple_command_r(t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*cmd;
	t_ast_lst	*prefix;

	prefix = cmd_prefix_r(lxr, ret);
	cmd = cmd_word_r(lxr, ret);
	if (!*ret || (!cmd && !prefix))
	{
		ast_lst_clear(&cmd);
		ast_lst_clear(&prefix);
		return (NULL);
	}
	else if (!cmd)
		return (prefix);
	else
		cmd->left = prefix;
	cmd->right = cmd_suffix_r(lxr, ret);
	if (!*ret)
		ast_lst_clear(&cmd);
	return (cmd);
}
