/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:52:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/21 12:08:02 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_ast_lst	*ast;

	char *line = readline("> ");
	ast = parser(line);
	printf("::%s:%d::\n", ast->left->left->left->data, ast->left->left->left->token);
	ast_lst_clear(&ast);
}

//("ARG=test" && HELLO=world) || echo $ARG | echo "$HELLO"
