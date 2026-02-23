/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:52:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/23 13:45:14 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	// t_ast_lst	*ast;

	// char *line = readline("> ");

	char	*data1 = malloc(17);
	ft_strlcpy(data1, "aaa$TEST bbb$ABC", 17);
	t_dictionary test1 = {.data = "test", .key = "ABC", .next = NULL};
	t_dictionary test = {.data = "1abc", .key = "TEST", .next = &test1};
	t_ast_lst one = {.data = data1, .left = NULL, .token = WORD, .right = NULL};
	expand(&one, &test);
	printf("TEST::%s::\n", one.data);
	// ast = parser(line);
	// ast_lst_clear(&ast);
}

//("ARG=test" && HELLO=world) || echo $ARG | echo "$HELLO"
