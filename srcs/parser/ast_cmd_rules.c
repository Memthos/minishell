/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:12:47 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/25 13:30:42 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast_lst	*cmd_suffix_r(t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*suffix;
	t_ast_lst	*tail;

	if (is_io_redirect(lxr))
		suffix = io_redirect_r(lxr, ret);
	else if (peek(lxr, WORD) || peek(lxr, ASSIGNMENT_W))
		suffix = ast_lst_new(lxr, ret, WORD);
	else
		return (NULL);
	tail = suffix;
	while (*ret && (is_io_redirect (lxr) || peek(lxr, WORD)
			|| peek(lxr, ASSIGNMENT_W)))
	{
		if (is_io_redirect(lxr))
			tail->right = io_redirect_r(lxr, ret);
		else
			tail->right = ast_lst_new(lxr, ret, WORD);
		if (!*ret)
			break ;
		tail = tail->right;
	}
	if (!*ret)
		ast_lst_clear(&suffix);
	return (suffix);
}

static t_ast_lst	*cmd_word_r(t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*cmd;

	cmd = NULL;
	if (peek(lxr, WORD) || peek(lxr, ASSIGNMENT_W))
		cmd = ast_lst_new(lxr, ret, 0);
	if (!*ret)
		ast_lst_clear(&cmd);
	return (cmd);
}

static t_ast_lst	*cmd_prefix_r(t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*prefix;
	t_ast_lst	*tail;

	if (is_io_redirect(lxr))
		prefix = io_redirect_r(lxr, ret);
	else if (peek(lxr, ASSIGNMENT_W))
		prefix = ast_lst_new(lxr, ret, 0);
	else
		return (NULL);
	tail = prefix;
	while (*ret && (is_io_redirect (lxr) || peek(lxr, ASSIGNMENT_W)))
	{
		if (is_io_redirect(lxr))
			tail->left = io_redirect_r(lxr, ret);
		else
			tail->left = ast_lst_new(lxr, ret, 0);
		if (!*ret)
			break ;
		tail = tail->left;
	}
	if (!*ret)
		ast_lst_clear(&prefix);
	return (prefix);
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
