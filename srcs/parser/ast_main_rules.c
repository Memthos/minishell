/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_main_rules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:03:21 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/17 16:22:40 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast_lst	*command_r(t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*cmd;
	t_lxr_lst	*tmp;

	tmp = lxr_lst_new(NULL, CMP_CMD, 0);
	if (!tmp)
	{
		*ret = 0;
		return (NULL);
	}
	if ((*lxr)->token == L_PAREN)
	{
		consume(lxr);
		cmd = ast_lst_new(&tmp, ret);
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

static t_ast_lst	*pipe_sequence_r(t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*cmd;
	t_ast_lst	*pipe;

	cmd = command_r(lxr, ret);
	if (!*ret)
		return (NULL);
	while (peek(lxr, PIPE))
	{
		pipe = ast_lst_new(lxr, ret);
		if (!*ret)
			break ;
		pipe->left = cmd;
		while (peek(lxr, NEW_LINE))
			consume(lxr);
		pipe->right = command_r(lxr, ret);
		if (!*ret)
			break ;
	}
	if (!*ret)
		ast_lst_clear(&pipe);
	return (pipe);
}

t_ast_lst	*and_or_r(t_lxr_lst **lxr, int *ret)
{
	t_ast_lst	*cmd;
	t_ast_lst	*and_or;

	cmd = pipe_sequence_r(lxr, ret);
	if (!*ret)
		return (NULL);
	while (*ret && (peek(lxr, AND_IF) || peek(lxr, OR_IF)))
	{
		and_or = ast_lst_new(lxr, ret);
		if (!*ret)
			break ;
		and_or->left = cmd;
		while (peek(lxr, NEW_LINE))
			consume(lxr);
		and_or->right = pipe_sequence_r(lxr, ret);
		if (!*ret)
			break ;
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
	{
		ast_lst_clear(&cmd);
		return (NULL);
	}
	while (peek(lxr, NEW_LINE))
		consume(lxr);
	return (cmd);
}
