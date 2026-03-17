/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_rules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:12:47 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/17 19:42:09 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cmd_arg_r(t_ast_lst **cmd, t_lxr_lst **lxr, t_status *status)
{
	t_ast_lst	*tmp;

	while (!*status && (peek(lxr, WORD) || peek(lxr, WILDCARD)))
	{
		tmp = NULL;
		if (!cmd || !*cmd)
			*cmd = ast_lst_new(lxr, status);
		else
		{
			if ((*cmd)->token != WORD && (*cmd)->token != WILDCARD)
			{
				tmp = *cmd;
				*cmd = ast_lst_new(lxr, status);
			}
			else
				ast_lst_last(*cmd, RIGHT)->right = ast_lst_new(lxr, status);
			if (*status && tmp)
				ast_lst_clear(&tmp);
			else if (tmp)
				(*cmd)->left = tmp;
		}
	}
}

static void	cmd_redirect_r(t_ast_lst **cmd, t_lxr_lst **lxr, t_status *status)
{
	while (!*status && is_io_redirect(lxr))
	{
		if (!cmd || !*cmd)
			*cmd = io_redirect_r(lxr, status, LEFT);
		else
			ast_lst_last(*cmd, LEFT)->left = io_redirect_r(lxr, status, LEFT);
	}
}

static t_ast_lst	*simple_command_r(t_lxr_lst **lxr, t_status *status)
{
	t_ast_lst	*cmd;

	cmd = NULL;
	while (!*status && (is_io_redirect(lxr) || peek(lxr, WORD)
		|| peek(lxr, WILDCARD)))
	{
		if (is_io_redirect(lxr))
			cmd_redirect_r(&cmd, lxr, status);
		else
			cmd_arg_r(&cmd, lxr, status);
	}
	if (*status)
		ast_lst_clear(&cmd);
	return (cmd);
}

t_ast_lst	*command_r(t_lxr_lst **lxr, t_status *status)
{
	t_ast_lst	*cmd;
	t_lxr_lst	*tmp;

	if ((*lxr)->token == L_PAREN)
	{
		tmp = lxr_lst_new(NULL, CMP_CMD, 0);
		if (!tmp)
		{
			*status = ALLOCATION_FAILURE;
			return (NULL);
		}
		consume(lxr);
		cmd = ast_lst_new(&tmp, status);
		if (*status)
			return (NULL);
		cmd->left = compound_cmd_r(lxr, status);
		if (!*status)
			cmd->right = redirect_loop(lxr, status);
	}
	else
		cmd = simple_command_r(lxr, status);
	if (*status)
		ast_lst_clear(&cmd);
	return (cmd);
}
