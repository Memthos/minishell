/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:12:47 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/02 13:04:09 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast_lst	*cmd_suffix_r(t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*suffix;
	t_ast_lst	*tail;

	if (is_io_redirect(lxr))
		suffix = io_redirect_r(lxr, ret, RIGHT);
	else if (peek(lxr, WORD) || peek(lxr, ASSIGNMENT_W))
		suffix = ast_lst_new(lxr, ret, WORD);
	else
		return (NULL);
	tail = ast_lst_last(suffix, RIGHT);
	while (*ret && (is_io_redirect (lxr) || peek(lxr, WORD)
			|| peek(lxr, ASSIGNMENT_W)))
	{
		if (is_io_redirect(lxr))
			tail->right = io_redirect_r(lxr, ret, RIGHT);
		else
			tail->right = ast_lst_new(lxr, ret, WORD);
		if (!*ret)
			break ;
		tail = ast_lst_last(tail, RIGHT);
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
		prefix = io_redirect_r(lxr, ret, LEFT);
	else if (peek(lxr, ASSIGNMENT_W))
		prefix = ast_lst_new(lxr, ret, 0);
	else
		return (NULL);
	tail = ast_lst_last(prefix, LEFT);
	while (*ret && (is_io_redirect (lxr) || peek(lxr, ASSIGNMENT_W)))
	{
		if (is_io_redirect(lxr))
			tail->left = io_redirect_r(lxr, ret, LEFT);
		else
			tail->left = ast_lst_new(lxr, ret, 0);
		if (!*ret)
			break ;
		tail = ast_lst_last(tail, LEFT);
	}
	if (!*ret)
		ast_lst_clear(&prefix);
	return (prefix);
}

static t_ast_lst	*simple_command_r(t_lxr_lst **lxr, int *ret)
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

t_ast_lst	*command_r(t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*cmd;
	t_lxr_lst	*tmp;

	if ((*lxr)->token == L_PAREN)
	{
		tmp = lxr_lst_new(NULL, CMP_CMD, 0);
		if (!tmp)
		{
			*ret = 0;
			return (NULL);
		}
		consume(lxr);
		cmd = ast_lst_new(&tmp, ret, 0);
		if (!*ret)
			return (NULL);
		cmd->left = compound_cmd_r(lxr, ret);
		if (*ret)
			cmd->right = redirect_loop(lxr, ret);
	}
	else
		cmd = simple_command_r(lxr, ret);
	if (!*ret)
		ast_lst_clear(&cmd);
	return (cmd);
}
