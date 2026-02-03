/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:12:47 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/03 13:47:23 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast_lst	*cmd_suffix_r(t_lxr_lst **lxr)
{
	t_ast_lst	*cmd;
	t_ast_lst	*suffix;
	char		*data;

	data = NULL;
	if (is_io_redirect (lxr) || peek(lxr, WORD))
	{
		data = ft_strcpy((*lxr)->data);
		cmd = ast_lst_new(data, (*lxr)->token, (*lxr)->p_dpt);
		consume(lxr);
	}
	else
		return (NULL);
	while (is_io_redirect (lxr) || peek(lxr, WORD))
	{
		data = ft_strcpy((*lxr)->data);
		suffix = ast_lst_new(data, (*lxr)->token, (*lxr)->p_dpt);
		consume(lxr);
		suffix->left = cmd;
		cmd = suffix;
	}
	return (cmd);
}

static t_ast_lst	*cmd_word_r(t_lxr_lst **lxr)
{
	t_ast_lst	*node;
	char		*data;

	node = NULL;
	if (peek(lxr, WORD) || peek(lxr, ASSIGNMENT_W))
	{
		data = ft_strcpy((*lxr)->data);
		ast_lst_new(data, (*lxr)->token, (*lxr)->p_dpt);
		consume(lxr);
	}
	return (node);
}

static t_ast_lst	*cmd_prefix_r(t_lxr_lst **lxr)
{
	t_ast_lst	*cmd;
	t_ast_lst	*prefix;
	char		*data;

	data = NULL;
	if (is_io_redirect (lxr) || peek(lxr, ASSIGNMENT_W))
	{
		data = ft_strcpy((*lxr)->data);
		cmd = ast_lst_new(data, (*lxr)->token, (*lxr)->p_dpt);
		consume(lxr);
	}
	else
		return (NULL);
	while (is_io_redirect (lxr) || peek(lxr, ASSIGNMENT_W))
	{
		data = ft_strcpy((*lxr)->data);
		prefix = ast_lst_new(data, (*lxr)->token, (*lxr)->p_dpt);
		consume(lxr);
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
