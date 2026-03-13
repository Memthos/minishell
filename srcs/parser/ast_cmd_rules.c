/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:12:47 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/13 19:36:45 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cmd_arg_r(t_ast_lst **cmd, t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*tmp;

	tmp = NULL;
	while (ret && (peek(lxr, WORD) || peek(lxr, ASSIGNMENT_W)))
	{
		if (!cmd || !*cmd)
			*cmd = ast_lst_new(lxr, ret, WORD);
		else
		{
			if ((*cmd)->token != WORD && (*cmd)->token != ASSIGNMENT_W)
				tmp = *cmd;
			ast_lst_last(*cmd, RIGHT)->right = ast_lst_new(lxr, ret, WORD);
			if (!ret && tmp)
				ast_lst_clear(&tmp);
			else if (tmp)
				(*cmd)->left = tmp;
		}
	}
}

static void	cmd_redirect_r(t_ast_lst **cmd, t_lxr_lst **lxr, int *ret)
{
	while (ret && is_io_redirect(lxr))
	{
		if (!cmd || !*cmd)
			*cmd = io_redirect_r(lxr, ret, LEFT);
		else
			ast_lst_last(*cmd, LEFT)->left = io_redirect_r(lxr, ret, LEFT);
	}
}

static t_ast_lst	*simple_command_r(t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*cmd;

	cmd = NULL;
	while (ret && (is_io_redirect(lxr) || peek(lxr, WORD)
		|| peek(lxr, ASSIGNMENT_W)))
	{
		if (is_io_redirect(lxr))
			cmd_redirect_r(&cmd, lxr, ret);
		else
			cmd_arg_r(&cmd, lxr, ret);
	}
	if (!ret)
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
