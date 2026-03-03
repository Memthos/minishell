/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:48:22 by juperrin          #+#    #+#             */
/*   Updated: 2026/03/02 13:39:07 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
