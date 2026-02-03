/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_base_rules.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:03:21 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/30 16:16:56 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast_lst	*pipe_sequence_r(t_lxr_lst **lxr)
{
	t_ast_lst	*cmd;
	t_ast_lst	*pipe;
	char		*data;

	cmd = simple_command_r(lxr);
	while (peek(lxr, PIPE))
	{
		data = ft_strcpy((*lxr)->data);
		pipe = ast_lst_new(data, (*lxr)->token, (*lxr)->p_dpt);
		consume(lxr);
		pipe->left = cmd;
		while (peek(lxr, NEW_LINE))
			consume(lxr);
		pipe->right = simple_command_r(lxr);
		cmd = pipe;
	}
	return (cmd);
}

static t_ast_lst	*and_or_r(t_lxr_lst **lxr)
{
	t_ast_lst	*cmd;
	t_ast_lst	*and_or;
	char		*data;

	cmd = pipe_sequence_r(lxr);
	while (peek(lxr, AND_IF) || peek(lxr, OR_IF))
	{
		data = ft_strcpy((*lxr)->data);
		and_or = ast_lst_new(data, (*lxr)->token, (*lxr)->p_dpt);
		consume(lxr);
		and_or->left = cmd;
		while (peek(lxr, NEW_LINE))
			consume(lxr);
		and_or->right = pipe_sequence_r(lxr);
		cmd = and_or;
	}
	return (cmd);
}

t_ast_lst	*complete_command_r(t_lxr_lst **lxr)
{
	t_ast_lst	*cmd;

	cmd = and_or_r(lxr);
	while (peek(lxr, NEW_LINE))
		consume(lxr);
}
