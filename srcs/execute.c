/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:54:56 by juperrin          #+#    #+#             */
/*   Updated: 2026/02/24 10:32:08 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**convert_ast(t_ast_lst *ast)
{
	t_uint	index;
	t_uint	size;
	char	**args;

	if (NULL == ast)
		return (NULL);
	size = ast_cmd_size(ast);
	args = (char **)malloc(sizeof(char *) * (size + 1));
	if (NULL == args)
		return (NULL);
	index = 0;
	while (index < size)
	{
		*(args + index) = ast->data;
		ast = ast->right;
		++index;
	}
	args[index] = NULL;
	return (args);
}

t_status	execute(t_shell *shell)
{
	char		**args;
	t_status	code;

	if (NULL == shell || NULL == shell->cmd_ast)
		return (FAILURE);
	args = convert_ast(shell->cmd_ast);
	if (NULL == args)
		return (FAILURE);
	code = get_command(*args)(args + 1, shell);
	(void)code;
	free(args);
	return (SUCCESS);
}
