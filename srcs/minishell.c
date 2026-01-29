/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:52:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/29 11:15:33 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char *test = malloc(sizeof(char) * 5);
	test[0] = 'T';
	test[0] = 'E';
	test[0] = 'S';
	test[0] = 'T';
	test[0] = '\0';
	ft_strjoin_sep(&test, "TEST2", '\0');
	// t_lxr_lst *lst = NULL;
	// char *line = readline("> ");
	// lexer(&lst, line);
	// while (lst)
	// {
	// 	printf("::%s::TOKEN=%d::P_DPT=%zu::\n", lst->data, lst->token, lst->p_dpt);
	// 	lst = lst->next;
	// }
}

//("ARG=test" && HELLO=world) || echo $ARG || echo "$HELLO"
