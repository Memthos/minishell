/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:48:22 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/01 13:29:02 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_uint	ast_cmd_count(t_ast_lst *ast)
{
	t_ast_lst	*tmp;
	t_uint		count;

	if (NULL == ast)
		return (0);
	count = 0;
	if (WORD == ast->token)
		count = 1;
	tmp = ast;
	while (tmp->left && WORD == tmp->token)
		tmp = tmp->left;
	count += ast_cmd_count(tmp->left);
	tmp = ast;
	while (tmp->right && WORD == tmp->token)
		tmp = tmp->right;
	count += ast_cmd_count(tmp->right);
	return (count);
}

t_uint	ast_cmd_size(t_ast_lst *ast)
{
	t_uint	size;

	size = 0;
	while (ast && WORD == ast->token)
	{
		ast = ast->right;
		++size;
	}
	return (size);
}

t_uint	ast_pipe_count(t_ast_lst *ast)
{
	t_uint	count;

	if (NULL == ast)
		return (0);
	count = 0;
	if (PIPE == ast->token)
		count = 1;
	count += ast_pipe_count(ast->left);
	count += ast_pipe_count(ast->right);
	return (count);
}

t_uint	ast_heredoc_count(t_ast_lst *ast)
{
	t_uint	count;

	if (NULL == ast)
		return (0);
	count = 0;
	if (DLESS == ast->token)
		count = 1;
	count += ast_heredoc_count(ast->left);
	return (count);
}

t_uint	ast_output_cmp_pipe_count(t_ast_lst *ast)
{
	t_uint	count;

	if (NULL == ast)
		return (0);
	count = 0;
	if (PIPE == ast->token && ast->left && CMP_CMD == ast->left->token)
		count = 1;
	count += ast_output_cmp_pipe_count(ast->left);
	count += ast_output_cmp_pipe_count(ast->right);
	return (count);
}

bool	is_cmp_pipe(t_ast_lst *node)
{
	if (NULL == node)
		return (false);
	if (node->left && CMP_CMD == node->left->token)
		return (true);
	if (node->right && CMP_CMD == node->right->token)
		return (true);
	return (false);	
}
