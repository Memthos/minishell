/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:52:18 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/28 14:08:25 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_list *lst = NULL;
	char *line = readline("> ");
	lexer(&lst, line);
	while (lst)
	{
		printf("::%s::TOKEN=%d::P_DPT=%zu::\n", lst->data, lst->token, lst->parenth_dpt);
		lst = lst->next;
	}
}

//("ARG=test" && HELLO=world) || echo $ARG || echo "$HELLO"
