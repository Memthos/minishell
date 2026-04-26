/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:48:22 by juperrin          #+#    #+#             */
/*   Updated: 2026/04/26 15:12:05 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_uint	ast_heredoc_count(t_ast_lst *ast, bool is_cmp)
{
	t_uint	count;

	if (NULL == ast)
		return (0);
	count = 0;
	if (DLESS == ast->token)
		count = 1;
	if (is_cmp)
		count += ast_heredoc_count(ast->left, is_cmp);
	else
		count += ast_heredoc_count(ast->right, is_cmp);
	return (count);
}
