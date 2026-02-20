/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:52:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/20 13:11:55 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_ast_lst	*ast;

	char *line = readline("> ");
	ast = parser(line);
	ast_lst_clear(&ast);
}

//("ARG=test" && HELLO=world) || echo $ARG | echo "$HELLO"
