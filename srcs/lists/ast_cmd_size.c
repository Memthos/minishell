/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:48:22 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/23 15:56:28 by juperrin         ###   ########.fr       */
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
